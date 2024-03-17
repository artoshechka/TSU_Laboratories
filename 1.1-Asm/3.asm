section .data
    user_message: db "Enter the number, please  ==>"
    len_user_message equ $-user_message

section .bss
    num1 resb 4
    num2 resb 4

section .text
   global _start
      _start:
      ; Сообщение о вводе
         mov eax, 4
         mov ebx, 1
         mov ecx, user_message
         mov edx, len_user_message
         int 80h
      ; Считываем и сохраняем пользовательский ввод
         mov eax, 3
         mov ebx, 0
         mov ecx, num1  
         mov edx, 4
         int 80h
      ; Сообщение о вводе
         mov eax, 4
         mov ebx, 1
         mov ecx, user_message
         mov edx, len_user_message
         int 80h
      ; Считываем и сохраняем пользовательский ввод
         mov eax, 3
         mov ebx, 0
         mov ecx, num2  
         mov edx, 4
         int 80h

      ; Пошаманим??
         mov eax,[num1]
         sub eax,'0'
         mov ebx,[num2]
         sub ebx,'0'
      ; Сравнение чисел
         cmp eax, ebx
         jle Mn
         xchg eax, ebx
      Mn:
      ; Вновь приводим числа к виду строк
         add eax, 30h
         add ebx, 30h
         mov [num1],eax
         mov [num2],ebx
      ; Вывод меньшего
         mov eax, 4
         mov ebx, 1
         mov ecx, num1
         mov edx, 4
         int 80h 
      ; Вывод большего
         mov eax, 4
         mov ebx, 1
         mov ecx, num2
         mov edx, 4
         int 80h

      ;ценоК
         mov eax, 1
         mov ebx, 0
         int 80h