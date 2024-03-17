section .data ;Сегмент Data Просим пользователя ввести число
    userMsg db 'Enter the number ==> '
    lenUserMsg equ $-userMsg ;Длина сообщения
    dispMsg db 'Imposrer is -> '
    lenDispMsg equ $-dispMsg

section .bss
    num1 resb 4
    num2 resb 4
    num3 resb 4
    num4 resb 4
    result resb 4
section .text
    global _start
        _start:
        ;Считываем и сохраняем пользовательский ввод
        mov eax, 4
        mov ebx, 1
        mov ecx, userMsg
        mov edx, lenUserMsg
        int 80h

        mov eax, 3
        mov ebx, 0
        mov ecx, num1
        mov edx, 4 
        int 80h

        ;Считываем и сохраняем пользовательский ввод 
        mov eax, 4
        mov ebx, 1
        mov ecx, userMsg
        mov edx, lenUserMsg
        int 80h

        mov eax, 3
        mov ebx, 0
        mov ecx, num2
        mov edx, 4 
        int 80h

        ;Считываем и сохраняем пользовательский ввод 
        mov eax, 4
        mov ebx, 1
        mov ecx, userMsg
        mov edx, lenUserMsg
        int 80h

        mov eax, 3
        mov ebx, 0
        mov ecx, num3
        mov edx, 4
        int 80h


        ;Считываем и сохраняем пользовательский ввод 
        mov eax, 4
        mov ebx, 1
        mov ecx, userMsg
        mov edx, lenUserMsg
        int 80h

        mov eax, 3
        mov ebx, 0
        mov ecx, num4
        mov edx, 4
        int 80h

        ;Imposter
        mov eax, 4
        mov ebx, 1
        mov ecx, dispMsg
        mov edx, lenDispMsg
        int 80h

        mov eax,[num1]
        sub eax,30h
        mov [num1],eax
        mov eax,[num2]
        sub eax,30h
        mov [num2],eax
        mov eax,[num3]
        sub eax,30h
        mov [num3],eax



        ; сравнение
        mov eax, [num2]
        cmp eax, [num1]
        je equal_ab ; переход если num1 == num2
        cmp eax, [num3]
        je equal_bc ; переход если num2 == num3

        ; num1 != num2 != num3
        mov eax, 2
        add eax, 30h
        mov [result], eax
        jmp END

        ; num1 != num2 == num3
        equal_bc: 
            mov eax, 1
            add eax, 30h
            mov [result], eax
            jmp END

        ; num1 == num2
        equal_ab: 
            cmp eax, [num3]
            je equal_abc ; переход если num1 == num2 == num3
            ; num1 == num2 != num3
            mov eax, 3
            add eax, 30h
            mov [result], eax
            jmp END

        ; num1 == num2 == num3
        equal_abc: 
            mov eax, 4
            add eax, 30h
            mov [result], eax
            jmp END

        END: 
            mov eax, 4
            mov ebx, 1
            mov ecx, result
            mov edx, 4
            int 80h
        ; Код выхода
        mov eax, 1
        mov ebx, 0
        int 80h