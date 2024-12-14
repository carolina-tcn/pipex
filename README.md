pipex: Manejo de Pipes en C 🔗💻

Es un proyecto que replica el comportamiento de una pipe en la shell, combinando redirección de entrada y salida
con la ejecución de comandos encadenados. El programa utiliza llamadas al sistema como pipe, fork, y execve para conectar comandos,
permitiendo una interacción fluida entre ellos.

Modo de uso:
El programa se ejecuta con la siguiente sintaxis:

bash:
./pipex archivo1 comando1 comando2 archivo2  

Esto es equivalente a la instrucción shell:
< archivo1 comando1 | comando2 > archivo2  
