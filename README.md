# Minishell
<div style="text-align: justify">
Minishell es un intérprete de comandos minimalista basado en Bash, uno de los shells más populares en sistemas Unix. Este proyecto, desarrollado en el lenguaje de programación C, ofrece una versión simplificada pero funcional de un shell Unix. Diseñado como una herramienta educativa y práctica.

## Principales librerías usadas:

### • <a href="https://github.com/dacortes/libft" target="_blank">libft.</a>

### • <a href="https://github.com/dacortes/minishell/tree/master/lib/readline" target="_blank">readline.</a>

## Compilación:
En este proyecto, se descargó e incluyó la librería readline. Para compilarla, se utilizaron las siguientes variables, flags, comandos y reglas en el Makefile del proyecto:

## Include readline:
Indicamos la ruta donde se encuentran los archivos de cabecera (headers) de la biblioteca readline y los incluimos en nuestro proyecto utilizando el flag -I. Este flag informa al compilador sobre la ubicación de los archivos de cabecera, permitiéndonos utilizar las funciones y estructuras definidas en la biblioteca durante la compilación de nuestro código fuente.
```make
INC = -I ./lib/readline/ #line 44
```
### Configure:
Este condicional en el Makefile realiza una verificación crucial antes de compilar el proyecto. Primero, verifica la existencia del archivo config.status en el directorio de la biblioteca readline.
```make
#line 73
conf:
	@if [ ! -f $(READL)config.status ]; then\
		cd $(READL) && ./configure &> /dev/null; \
		echo "✅ ==== $(G)$(ligth)Create config.status$(E)==== ✅"; \
	fi
```
Si el archivo config.status no existe, el condicional ejecuta el script <b>./configure</b> este script prepara el entorno para la compilación. Configura las opciones, detecta dependencias del sistema, ajusta rutas y realiza otras tareas esenciales para asegurarse de que el código se compile correctamente en el entorno del usuario.

Luego, para garantizar que este archivo no se incluya en el repositorio, añadimos su nombre de archivo al archivo .gitignore.
```c
#line 12
config.status
```

Finalmente, cuando se completa el proceso de configuración y se crea el archivo config.status.

Para compilar correctamente los objetos, es necesario informar al sistema que la biblioteca readline está disponible. Para hacer esto, creamos una macro llamada <b>READLINE_LIBRARY</b> con un valor de 1 usando el flag <b>-D READLINE_LIBRARY=1</b>.
```make
$(CC) -MMD $(FLAGS) -c -D READLINE_LIBRARY=1 $< -o $@ $(INC) #line 87
```
Por último, agregamos el flag –ltermcap en nuestra regla para compilar el programa.

El flag -ltermcap en el comando de compilación indica al compilador que debe vincular el programa con la biblioteca termcap. Esta biblioteca proporciona funcionalidades para el control avanzado de la terminal, permitiendo que el programa interactúe con el terminal de manera más sofisticada, incluyendo el manejo de teclas especiales, el posicionamiento del cursor y otras características avanzadas de la terminal. La opción -ltermcap indica que se debe utilizar esta biblioteca durante el proceso de enlace para asegurar que el programa pueda utilizar estas funcionalidades de la terminal.

## Bugs:
Cuando el proceso de compilación se interrumpe y se fuerza a finalizar mediante el makefile, se genera un archivo config.status incorrecto. Esto resulta en un error de compilación al intentar compilar nuevamente, esto también pasa si se cambia el nombre del directorio que contiene el proyecto.
### Solución:
Ejecuta nuevamente el script configure en el directorio del proyecto. Esto generará un nuevo archivo config.status basado en la configuración actual del proyecto.
```bash
cd lib/readline
#ejecutas el configure
./configure
```
Ahora, puedes volver a compilar el proyecto utilizando el makefile. Esto debería generar los archivos de salida correctamente.
```bash
cd ../../ && make
```

### Comprobación Adicional:

Si el problema persiste, verifica si hay otros archivos generados que podrían estar causando conflictos (por ejemplo, archivos de configuración antigua). Elimina esos archivos y vuelve a ejecutar el script configure y make según sea necesario.

## Nota:
Este script está desarrollado utilizando GNU Bash, versión 3.2.57, y se ejecuta en sistemas operativos Darwin Kernel, versión 19.6.0.

Comandos en bash para saber la versión que tienes:
 ```bash
bash --version
uname -a
```
</div>