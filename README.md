# Утилита для потокового вывода содержимого файла в CLI 

## Задача

Реализовать [утилиту](https://ru.wikipedia.org/wiki/%D0%A3%D1%82%D0%B8%D0%BB%D0%B8%D1%82%D0%B0) PrintFile выводящую в стандартный  поток вывода содержимое(частичное содержимое)
для указанного файла.

Программа должна поддерживать следующие аргументы командной строки (опции):

**-l, --lines=n**   вывести только n (только положительное) первых(последних) строк файл  (необязательный аргумент, по-умолчанию выводим все)

**-t, --tail**      вывод n последний строк файла (необязательный аргумент)

**-d, --delimiter=c**  символ по которому определяется конец строки (нeобязательный, по-умолчанию '\n')

Название файла и опции передаются через аргументы командной строки в следующем формате:

_**PrintFile.exe [OPTION] filename**_

### Примеры запуска программы:

*PrintFile.exe filename*

*PrintFile.exe filename*

*PrintFile.exe --tail --lines=10 filename*

*PrintFile.exe -l 2 filename*

*PrintFile.exe -d '\t' filename*

*PrintFile.exe  filename -t -l 10*
