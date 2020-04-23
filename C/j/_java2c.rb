# Make sure the Java code uses THIS for fields.
# Use Cleanup "use this" before converting code.
@@classname = ""

def struct
  "struct #{@@classname}"
end

def convert_line(line)

  if line =~ / (class|interface) (\w+)/
    @@classname = $2
  end

  typeName = /[A-Z]\w*/
  type = /(?:#{typeName}|boolean|int|void|double|float|char\*)(?:\[\])?/
  fieldName = /[a-z]\w*/

  line = line.
    # remove
    sub(/^package (.*);/, ""). # package statement
    sub(/^import (.*);/, "").
    sub(/@Override/, "").
    sub(/@SuppressWarnings\("unchecked"\)/, "").
    # map
    gsub(/String /, "char* ").
    sub(/public class (#{typeName}) implements (#{typeName}) \{/, "struct \\1 {\n\t\\2 base;").
    sub(/public class (#{typeName}) \{/, "struct \\1 {").
    gsub(/(?:private|protected) (?:final )?(#{type}) (#{fieldName})/, "\\1 \\2"). # fields

    sub(/public #{@@classname}\(([^)]*)\) \{/, # constructor declaration
      "};\n #{struct}* make#{@@classname}(\\1) {\n" +
      "  #{struct} *this = (#{struct} *)malloc(sizeof(#{struct}));").
    # add return this;
    gsub(/public (#{type}) (#{fieldName})\(([^)]*)\) \{/, "\\1 \\2(#{struct} *this, \\3) {"). # this
    gsub(/, \)/, ")").
    gsub(/throw new UnsupportedOperationException\(("[^"]+")\);/, "printf(\"Unsupported Operation %s\\n\", \\1); exit(1);").
    gsub(/^\}\n/, ""). # remove end of class
    gsub(/this\./, "this->") # fix .

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

  if line =~ /(?:: |extends |implements |new )(#{type})/
    @@used_types << $1
  end

  line.rstrip
end

def convert_source(lines)
  @@classname = ""
  @@used_types = []
  code = lines.map { |line| convert_line(line) }

  imports = @@used_types.
    find_all { |t| t =~ /^[A-Z]/ }.
    reject { |t| t == 'Random' }.
    sort.uniq.
    map { |t| "#include \"#{to_c_file_name(t)}.h\";" }

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

Dir["Price.java"].each do |java_file|
  java_lines = IO.readlines(java_file)
  c_lines = convert_source(java_lines)
  c_file = to_c_file_name(java_file[/^[^.]+/]) + ".c"
  save(c_file, c_lines)
end
