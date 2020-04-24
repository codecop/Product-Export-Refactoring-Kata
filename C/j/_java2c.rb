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

  typeName = /[A-Z]\w*/
  type = /(?:#{typeName}|boolean|int|long|void|float|double|char\*)(?:\[\])?/
  fieldName = /[a-z]\w*/

  line = line.
    # remove
    sub(/^package (.*);/, ''). # package statement
    sub(/^import (.*);/, ''). # imports
    sub(/@Override/, ''). # annotations
    sub(/@SuppressWarnings\("[^"]+"\)/, '').
    # map types
    gsub(/String /, 'char* ').
    gsub(/boolean /, 'bool ').
    # map fields
    gsub(/(?:private|protected) (?:final )?(#{type}) (#{fieldName})/, "\\1 \\2").
    # map class struct
    sub(/public class (#{typeName}) implements (#{typeName}) \{/, "struct \\1 {\n\t\\2 base;").
    sub(/public class (#{typeName}) \{/, "struct \\1 {").
    gsub(/^\}\n/, ''). # remove end of class
    # map declarations
    sub(/public #{@@classname}\(([^)]*)\) \{/, # constructor declaration
      "};\n\n" + # end of struct
      "  #{struct}* make#{@@classname}(\\1) {\n" +
      "  #{struct} *this = (#{struct} *)malloc(sizeof(#{struct}));").
    # add return this; - found by compile error
    # add this
    gsub(/public (#{type}) (#{fieldName})\(([^)]*)\) \{/, "\\1 \\2(#{struct} *this, \\3) {"). # this
    gsub(/, \)/, ')'). # fix arguments introduced by this
    gsub(/this\./, 'this->'). # fix .
    # map single statements
    gsub(/throw new UnsupportedOperationException\(("[^"]+")\);/, 'printf("Unsupported Operation %s\\n", \\1); exit(1);').

#    sub(/System\.out\.println/, "console.log"). # println
#    sub(/(public|private) (#{type}) (\w+\([^)]*\))/, "\\1 \\3: \\2"). # method return type order
#    sub(/(#{type}) (\w+\([^)]*\));/, "\\2: \\1;"). # abstract method return type order
#    sub(/(private|public|^\s*) (#{type}) (\w+)(;| |=)/, "\\1 \\3: \\2\\4"). # fields type order
#    gsub(/(\(| )(#{type}) (\w+)(,|\))/, "\\1\\3: \\2\\4"). # parameter type order
#    # map types
#    # gsub(/(#{type})\[\]/, "Array<\\1>"). # array type
#    gsub(/String/, "string"). # string type
#    sub(/new LinkedList\(\)/, "[]").
#    gsub(/LinkedList/, "any[]").
#    gsub(/Integer/, "number").
#    gsub(/: int/, ": number").
#    # map operators
#    gsub(/ == /, " === ").
#    gsub(/ != /, " !== ")
    sub(/foobarbaz/, 'foobarbaz') # fake last statement

  if line =~ /(?:: |extends |implements |new )(#{type})/
    @@used_types << $1
  elsif line =~ /(#{type}) #{fieldName}/
    @@used_types << $1
  elsif line =~ /malloc\(/
    @@used_types << 'stdlib.h'
  elsif line =~ /bool /
    @@used_types << 'stdbool.h'
  elsif line =~ /printf/
    @@used_types << 'stdio.h'
  end

  line.rstrip
end

def convert_source(lines)
  @@classname = ''
  @@used_types = []
  code = lines.map { |line| convert_line(line) }

  imports = @@used_types.
    find_all { |t| t =~ /^[A-Z]/ }.
    reject { |t| t == 'Random' }.
    sort.uniq.
    map { |t| "#include \"#{to_c_file_name(t)}.h\"" }

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

Dir['Product.java'].each do |java_file|
  java_lines = IO.readlines(java_file)
  c_lines = convert_source(java_lines)
  c_file = to_c_file_name(java_file[/^[^.]+/]) + '.c'
  save(c_file, c_lines)
end
