section .data
newLineMsg db 0xA, 0xD
newLineLen equ $-newLineMsg
RESULT_MSG:     db 'Result = '
RESULT_MSG_LEN:  equ $-RESULT_MSG
RESULT_MSG01:     db 'Result = 1'
RESULT_MSG_LEN01:  equ $-RESULT_MSG


buffer db 250, 0


section .bss
s resb 512 ; зарезирвированно 512 байта
len resd 2
num resb 512

section .text
global _start

_start:
; читаем строку
mov eax, 3
mov ebx, 0
mov ecx, num
mov edx, num ; число символов для чтения
int 80h
;***********************************************************
xor ecx, ecx ; обнуляем
xor eax, eax
xor edx, edx
xor esi, esi
BeginChar:
xor eax, eax
mov al, [num + esi] ; читаем символ из строки
cmp eax, 0x0A ; проверяем на конец строки
je .EndChar ; завершаем обработке если конец строки
sub eax, '0' ; вычитаем ascii
mov ebx, eax ; переместили для временного хранения
mov eax, edx ; перемещаем предыдущий результат
mov edx, 10
mul edx
add eax, ebx ; сумируем с предыдущим результатом
inc esi ; увеличиваем смещение
mov edx, eax ; результат перемещаем в edx
jmp BeginChar
.EndChar:
mov ecx, edx

cmp edx, 1
je one_or_zero

cmp edx, 0
je one_or_zero

;***********************************************************
mov eax,1 ;В EAX будет факториал, на это число мы будем умножать все остальные. выставляем 1
; mov ecx,10 ; В ECX число факториал которого нужно найти.
fact:
mul ecx ; умножаем eax на ecx
dec ecx ; вычитаем из ecx еденицу
cmp ecx,1 ; проверяем не равен ли ECX еденице
jne fact ; JNE= JUMP if NOT EQUAL - переход если неравно. если ECX != 1 - переходим на следующую итерацию.

;***********************************************************
; mov eax, 1234560856 ; выводимое число
lea edi, [s] ; загружает в edi регистр адрес куда будут складываться символов
xor ecx, ecx ; XOR операнд числа с самим собой меняет операнд на 0. Это используется для очистки регистра.
mov ebx, 10
.ToAscii:
xor edx, edx ; обнуляем
inc ecx ; инкремент кол-во цифр
div ebx ; делит eax на ebx результат записывается eax а остаток в edx
add edx, '0' ; добавляем "0" для получения ASCII
push edx ; записываем в стек

cmp eax, 0 ; сравнить можно использвать test eax, eax
jnz .ToAscii ; Команда "переход, если содержимое аккумулятора не равно нулю" JNZ <метка>
mov [len], ecx ; записываем число обработанных чисел
xor esi, esi
.store:
xor eax, eax
pop eax ; читаем из стека
mov [s + esi], al
inc esi
cmp ecx, esi
jne .store
jmp end
;***********************************************************
; вывод


one_or_zero:
mov eax,4            
mov ebx,1            
mov ecx,RESULT_MSG01     
mov edx,RESULT_MSG_LEN01 
int 80h
jmp exit  


end:
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

exit:
mov eax,1 ; The system call for exit (sys_exit)
mov ebx,0 ; Exit with return code of 0 (no error)
int 80h;