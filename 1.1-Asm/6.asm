section .data
 BASE_MSG:     db 'Enter the base',10
 BASE_MSG_LEN:  equ $-BASE_MSG          
 EXP_MSG:     db 'Enter the Exponent',10
 EXP_MSG_LEN:  equ $-EXP_MSG     
 ERR_CHAR:     db 'Symbol error',10
 ERR_CHAR_LEN:  equ $-ERR_CHAR    
 ERR_NUM_CHAR:     db 'Number Excess',10
 ERR_NUM_CHAR_LEN:  equ $-ERR_NUM_CHAR    
 RESULT_MSG:     db 'Result = '
 RESULT_MSG_LEN:  equ $-RESULT_MSG
 RESULT_0_MSG:     db 'Result = 0'
 RESULT_0_MSG_LEN:  equ $-RESULT_0_MSG  
 RESULT_1_MSG:     db 'Result = 1'
 RESULT_1_MSG_LEN:  equ $-RESULT_1_MSG
 RESULT_11_MSG:     db 'Result = -1'
 RESULT_11_MSG_LEN:  equ $-RESULT_11_MSG    
 OVERFLOW_MSG:     db 'Overflow'
 OVERFLOW_MSG_LEN:  equ $-OVERFLOW_MSG
 
 
section .bss
    Character_String    resb 12 ; зарезирвированно 12 байта (знак, 10 символов, символ ввода (0x0A))
    Length_String       resd 1
    Sign                resd 1
    
    s       resb 512 ; зарезирвированно 512 байта
    len     resd 2
    
section .text
    global _start

_start:
 mov eax,4            
 mov ebx,1            
 mov ecx,BASE_MSG     
 mov edx,BASE_MSG_LEN 
 int 80h              
;***********************************************************
 ; читаем основание
 mov eax, 3
 mov ebx, 0
 mov ecx, Character_String
 mov edx, Length_String        ; число символов для чтения
 int 80h
;***********************************************************
 xor ecx, ecx        ; обнуляем
 xor edx, edx
 xor esi, esi
 xor ebx, ebx
 
 .BeginChar:
  xor eax, eax
  mov al, [Character_String + esi] ; читаем символ из строки
  inc esi
  cmp al, 0x0A    ; проверяем конец строки "0А"
  je .EndChar     ; завершаем обработке если конец строк
  cmp al, '-'     ; проверяем знак "-"
  jne .Digit      ; завершаем обработке если конец строк
  cmp esi, 1 
  jne .ErrChar
  mov [Sign], al
  jmp .BeginChar
 .Digit: 
  cmp al, '0'     ; проверяем на диапозон "0"- "9"
  jb .ErrChar
  cmp al, '9'     
  ja .ErrChar
  sub eax, '0'    ; вычитаем ascii "0"
  mov ebx, eax        ; переместили для временного хранения
  mov eax, edx        ; перемещаем предыдущий результат
  mov edx, 10
  mul edx
  add eax, ebx        ; сумируем с предыдущим результатом
  mov edx, eax        ; результат перемещаем в edx
  inc ecx         ; считаем количество символов inc esi
  cmp ecx, 10     ; Проверка на максимальное число цифр
  ja .ErrNumChar
  jmp .BeginChar
 .EndChar:    
  ; Проверка на 0 
  cmp edx, 0     
  je .ResultNull
  cmp edx, 1     
  je .ResultONE
  push edx  ; Сохраняем в стек
;***********************************************************
;***********************************************************
; Читаем степень
 mov eax,4            
 mov ebx,1            
 mov ecx,EXP_MSG     
 mov edx,EXP_MSG_LEN 
 int 80h              

 mov eax, 3
 mov ebx, 0
 mov ecx, Character_String
 mov edx, Length_String        ; число символов для чтения
 int 80h
;***********************************************************
 xor ecx, ecx        ; обнуляем
 xor edx, edx
 xor esi, esi
 xor ebx, ebx
 
 .BeginCharExp:
  xor eax, eax
  mov al, [Character_String + esi] ; читаем символ из строки
  inc esi
  cmp al, 0x0A    ; проверяем конец строки "0А"
  je .EndCharExp     ; завершаем обработке если конец строк
; гдето должна быть проверкана отсутствие символов!!!!!!!!!!!!
  cmp al, '0'     ; проверяем на диапозон "0"- "9"
  jb .ErrChar
  cmp al, '9'     
  ja .ErrChar
  sub eax, '0'    ; вычитаем ascii "0"
  mov ebx, eax    ; переместили для временного хранения
  mov eax, edx    ; перемещаем предыдущий результат
  mov edx, 10
  mul edx
  add eax, ebx        ; сумируем с предыдущим результатом
  mov edx, eax        ; результат перемещаем в edx
  inc ecx         ; считаем количество символов inc esi
  cmp ecx, 10     ; Проверка на максимальное число цифр
  ja .ErrNumChar
  jmp .BeginCharExp
 .EndCharExp:    
  mov eax, edx
  ; Проверка на 0 
  cmp eax, 0     ; проверяем что результат не равен 0 иначе переходим к выдачерезультата
  jne .ResultNotOne
  mov eax, 1
  jmp .Result
 .ResultNotOne:  
  cmp eax, 1     ; проверяем что результат не равен 1 иначе переходим к выдачерезультата
  jne .ResultNotBase
  pop eax
  jmp .Result
  .ResultNotBase:
;  push eax  ; Сохраняем в стек
;***********************************************************
;Проверка на четность

mov ebx, eax ; степень
 ror eax, 1
 jc .Odd
 mov eax, 0
 mov [Sign], eax
 .Odd:

;***********************************************************
 dec ebx
 
 pop esi        ; основание
 mov edx, esi   ; для первой суммы
 mov eax, esi
 dec esi        ; Количество суммирований -1 
 
 .CntExp:
 mov ecx, esi   ; тут лучше переменную
 .CntMult:
 add eax, edx 
 jc .Overflow   ;jo .Overflow проверка на переполнение
 loop .CntMult
 mov edx, eax   ; меняем слагаемое
 dec ebx        ; степень - 1
 cmp ebx, 0     ; проверяем что результат не равен 0 иначе переходим к результату
 jne .CntExp
 
 
;***********************************************************


 .Result:
 ; Преобразование в ASCII исходное число в eax
  xor ecx, ecx        ; XOR операнд числа с самим собой меняет операнд на 0. Это используется для очистки регистра.
  lea edi, [s]        ; загружает в edi регистр адрес куда будут складываться символов
  mov ebx, 10
 .ToAscii:
   xor edx, edx    ; обнуляем 
   inc ecx         ; инкремент кол-во цифр
   div ebx         ; делит eax на ebx результат записывается eax а остаток в edx
   add edx, '0'    ; добавляем "0" для получения ASCII
   push edx        ; записываем в стек
   cmp eax, 0  ; сравнить  можно использвать  test eax, eax
   jnz .ToAscii    ; Команда "переход, если содержимое аккумулятора не равно нулю" JNZ <метка>
   
   ; выводим знак
  mov eax, [Sign]
  cmp eax, 0
  je .NotSign
  push eax
  inc ecx
  mov [len], ecx
  .NotSign:
   
   mov [len], ecx  ; записываем число обработанных чисел
   xor esi, esi
   
   
   
 .store:
    xor eax, eax
    pop eax     ; читаем из стека
    mov [s + esi], al
    inc esi
    cmp ecx, esi 
    jne .store
;***********************************************************
 ; вывод результата
 
  mov eax,4            
  mov ebx,1            
  mov ecx,RESULT_MSG     
  mov edx,RESULT_MSG_LEN 
  int 80h             
 
  mov eax, 4
  mov ebx, 1
  mov ecx, s
  mov edx, [len]
  int 80h
  jmp .Exit 
 
; Вывод нулевого результата 
 .ResultNull:
  mov eax,4            
  mov ebx,1            
  mov ecx,RESULT_0_MSG     
  mov edx,RESULT_0_MSG_LEN 
  int 80h             
  jmp .Exit
 
  .One:
  mov eax,4            
  mov ebx,1            
  mov ecx,RESULT_11_MSG     
  mov edx,RESULT_11_MSG_LEN 
  int 80h             
  jmp .Exit
  .ResultONE:
  mov al, [Sign]
  cmp al,'-'
  je .One
  mov eax,4            
  mov ebx,1            
  mov ecx,RESULT_1_MSG     
  mov edx,RESULT_1_MSG_LEN 
  int 80h             
  jmp .Exit
  


;***********************************************************
 .ErrChar:
 mov eax,4            
 mov ebx,1            
 mov ecx, ERR_CHAR     
 mov edx, ERR_CHAR_LEN 
 int 80h   
 jmp .Exit
;***********************************************************
 .ErrNumChar:
  mov eax,4            
  mov ebx,1            
  mov ecx, ERR_NUM_CHAR     
  mov edx, ERR_NUM_CHAR_LEN
  int 80h   
  jmp .Exit
;***********************************************************
 .Overflow:
  mov eax,4            
  mov ebx,1            
  mov ecx, OVERFLOW_MSG     
  mov edx, OVERFLOW_MSG_LEN
  int 80h
  
 .Exit: 
    mov eax,1            ; The system call for exit (sys_exit)
    mov ebx,0            ; Exit with return code of 0 (no error)
    int 80h;