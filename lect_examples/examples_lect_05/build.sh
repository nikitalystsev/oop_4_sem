#!/bin/bash

mkdir -p ./out

if [ -n "$1" ]; then
  # Если передан номер примера, компилируем соответствующий файл
  example_file="src/05_${1}.cpp"
  
  if [ -f "$example_file" ]; then
    g++ -std=c++20 -Wall -Werror -pedantic -Wextra -Iinc -Wvla -c "${example_file}" -o "out/05_${1}.o"
    g++ "out/05_${1}.o" -o "05_${1}.exe"
  else
    echo "Пример с номером $1 не найден"
  fi
else
  # Если номер не передан, компилируем все примеры по отдельности
  for example_file in "src/05_"*.cpp; do
    if [ -f "$example_file" ]; then
      filename=$(basename -- "$example_file")
      filename="${filename%.*}"
      g++ -std=c++20 -Wall -Werror -pedantic -Wextra -Iinc -Wvla -c "${example_file}" -o "out/${filename}.o"
      g++ "out/${filename}.o" -o "${filename}.exe"
    fi
  done
fi