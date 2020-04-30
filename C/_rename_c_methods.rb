# Rename all methods in C and H to be snake_case.

def convert_line(line)

  # type = /(?:const )?(?:[a-zA-Z_]+|struct \w+)\*?/
  badMethodName = /[a-z]+[A-Z]\w+/
  # declaration = /^\s*(?:extern |static )?#{type} #{badMethodName}\(/
  declaration = /(?: |\))(#{badMethodName})\(/
  # method name in declaration after type
  # method name in expression after operator
  # method name in expression with cast

  if line =~ declaration
    name = $1
    new_name = to_snake(name)
    line = line.gsub(/#{name}\(/, new_name + '(')
  end

  line.rstrip
end

def to_snake(name)
  name.gsub(/([A-Z])/, '_\\1').downcase
end

def convert_source(lines)
  lines.map { |line| convert_line(line) }
end

def save(name, lines)
  open(name, 'w') { |f|
    lines.each { |line| f.puts line }
  }
end

(Dir['*.c'] + Dir['*.h']).each do |file|
  puts "--- converting #{file}"
  old_lines = IO.readlines(file)
  new_lines = convert_source(old_lines)
  if old_lines != new_lines
    save(file, new_lines)
  end
end
