# Minishell
<div style="text-align: justify">
Minishell es un intérprete de comandos minimalista basado en Bash, uno de los shells más populares en sistemas Unix. Este proyecto, desarrollado en el lenguaje de programación C, ofrece una versión simplificada pero funcional de un shell Unix. Diseñado como una herramienta educativa y práctica.

## Principales librerías usadas:

### <a href="https://github.com/dacortes/libft" target="_blank">libft.</a>

### <a href="https://github.com/dacortes/minishell/tree/master/lib/readline" target="_blank">readline.</a>

## Compilación(Makefile):
En este proyecto, se descargó e incluyó la librería readline. Para compilarla, se utilizaron las siguientes variables, flags, comandos y reglas en el Makefile del proyecto:
```make
#Especificamos la ruta de los headers
INC = -I ./lib/readline/ #line 44
$(CC) -MMD $(FLAGS) -c -D READLINE_LIBRARY=1 $< -o $@ $(INC)
```


## Nota:
Este script está desarrollado utilizando GNU Bash, versión 3.2.57, y se ejecuta en sistemas operativos Darwin Kernel, versión 19.6.0.

Comandos en bash para saber la versión que tienes:
 ```bash
bash --version
uname -a
```
</div>