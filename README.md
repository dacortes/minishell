# Minishell
<div style="text-align: justify">
Minishell es un intérprete de comandos minimalista basado en Bash, uno de los shells más populares en sistemas Unix. Este proyecto, desarrollado en el lenguaje de programación C, ofrece una versión simplificada pero funcional de un shell Unix. Diseñado como una herramienta educativa y práctica.

## Principales librerías usadas:

### <a href="https://github.com/dacortes/libft" target="_blank">libft.</a>

### <a href="https://github.com/dacortes/minishell/tree/master/lib/readline" target="_blank">readline.</a>

## Compilación:
En este proyecto, se descargó e incluyó la librería readline. Para compilarla, se utilizaron las siguientes variables, flags, comandos y reglas en el Makefile del proyecto:

Indicamos la ruta donde se encuentran los archivos de cabecera (headers) de la biblioteca readline y los incluimos en nuestro proyecto utilizando el flag -I. Este flag informa al compilador sobre la ubicación de los archivos de cabecera, permitiéndonos utilizar las funciones y estructuras definidas en la biblioteca durante la compilación de nuestro código fuente.
```make
INC = -I ./lib/readline/ #line 44
```
Para compilar correctamente los objetos, es necesario informar al sistema que la biblioteca readline está disponible. Para hacer esto, creamos una macro llamada <b>READLINE_LIBRARY</b> con un valor de 1 usando el flag <b>-D READLINE_LIBRARY=1</b>.
```make
$(CC) -MMD $(FLAGS) -c -D READLINE_LIBRARY=1 $< -o $@ $(INC) #line 87
```

## Nota:
Este script está desarrollado utilizando GNU Bash, versión 3.2.57, y se ejecuta en sistemas operativos Darwin Kernel, versión 19.6.0.

Comandos en bash para saber la versión que tienes:
 ```bash
bash --version
uname -a
```
</div>