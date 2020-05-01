# Make sure the Java code uses THIS for fields.
# Use Cleanup "use this" before converting code.
@@classname = ''

def struct
  "struct #{@@classname}"
end

def convert_line(line)

  if line =~ / (class|interface) (\w+)/
    @@classname = $2
  end

  typeName = /[A-Z]\w*(?:<\w*>)?/
  type = /(?:#{typeName}|boolean|int|long|void|float|double)(?:\[\])?\*?/
  fieldName = /[a-z]\w*/

  line = line.
    # remove
    sub(/^package (.*);/, ''). # package statement
    sub(/^import (.*);/, ''). # imports
    sub(/@Override/, ''). # annotations
    sub(/@SuppressWarnings\("[^"]+"\)/, '').

    # map fields
    gsub(/(?:private|protected) (?:final )?(#{type}) (#{fieldName})/, "\\1 \\2").

    # map class struct
    sub(/public class (#{typeName}) implements (#{typeName}) \{/, "struct \\1 {\n\t\\2 base;").
    sub(/public class (#{typeName}) extends (#{typeName}) \{/, "struct \\1 {\n\t\\2 base;").
    sub(/public class (#{typeName}) \{/, "struct \\1 {").
    sub(/public class (#{typeName})\s$/, "struct \\1").
    gsub(/^\}\n/, ''). # remove end of class

    # map constructor
    sub(/public #{@@classname}\(([^)]*)\) \{/, # constructor declaration
      "};\n\n" + # end of struct
      "    #{struct}* make#{@@classname}(\\1) {\n" +
      "        #{struct} *this = (#{struct} *)malloc(sizeof(#{struct}));").
    # ... add return this; - found by compile error

    # add this
    gsub(/public (#{type}) (#{fieldName})\(([^)]*)\) \{/, "\\1 #{@@classname}\\2(#{struct} *this, \\3) {"). # this
    gsub(/, \)/, ')'). # fix arguments introduced by this
    gsub(/this\./, 'this->'). # fix .

    # map methods
    gsub(/public static /, '').
    gsub(/private static /, 'static ').
    gsub(/new (\w+)\(/, 'make\\1(').

    # map single statements
    gsub(/throw new UnsupportedOperationException\(("[^"]+")\);/, 'printf("Unsupported Operation %s\\n", \\1); exit(1);').

    # map comments
    gsub(/\/\*\*/, '/*').
    gsub(/\/\/(.*)$/, '/*\\1 */').

    # map types
    gsub(/String /, 'const char* ').
    gsub(/boolean /, 'bool ').
    gsub(/Collection<(#{typeName})> /, 'struct LinkedList* ').
    gsub(/Date /, 'time_t ').

    # fake last statement
    sub(/foobarbaz/, 'foobarbaz')

  badMethodName = /[a-z]+[A-Z]\w+/
  badMethodUse = /(?: |\))(#{badMethodName})\(/
  # method name in declaration after type
  # method name in expression after operator
  # method name in expression with cast

  while line =~ badMethodUse
    name = $1
    new_name = to_snake(name)
    line = line.gsub(/#{name}\(/, new_name + '(')
  end

  if line =~ /(?:: |extends |implements |new )(#{type})/
    @@used_types << $1
  end
  if line =~ /(#{type}) #{fieldName}/
    @@used_types << $1.sub(/\*$/, '')
  end
  if line =~ /time_t /
    @@used_types << 'time'
  end
  if line =~ /malloc/
    @@used_types << 'stdlib'
  end
  if line =~ /bool /
    @@used_types << 'stdbool'
  end
  if line =~ /struct LinkedList/
    @@used_types << 'LinkedList'
  end
  if line =~ /printf/
    @@used_types << 'stdio'
  end

  line.rstrip
end

def to_snake(name)
  name.gsub(/([A-Z])/, '_\\1').downcase
end

def convert_source(lines)
  @@classname = ''
  @@used_types = []
  code = lines.map { |line| convert_line(line) }

  imports = @@used_types.
    # find_all { |t| t =~ /^[A-Z]/ }.
    reject { |t| t == 'Random' }.
    sort.uniq.
    map do |t|
      t =~ /^[a-z]/ ?
      "#include <#{to_c_file_name(t)}.h>" :
      "#include \"#{to_c_file_name(t)}.h\""
    end

  imports + code
end

def save(name, lines)
  open(name, 'w') { |f|
    lines.each { |line| f.puts line }
  }
end

def to_c_file_name(java_name)
  # same file name
  java_name
end

Dir['SampleModelObjects.java'].each do |java_file|
  java_lines = IO.readlines(java_file)
  c_lines = convert_source(java_lines)
  c_file = to_c_file_name(java_file[/^[^.]+/]) + '.c'
  save(c_file, c_lines)
end
