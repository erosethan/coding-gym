# Coding Gym

## Objetivo

Soy Ethan Jimenez, programo desde que estaba en preparatoria y he sido participante de múltiples concursos de programación a nivel internacional. Actualmente resido en Redmond, Washington, y soy ingeniero de software en Microsoft.

Siempre me ha gustado enseñar y tengo mucha pasión por las ciencias de la computación como parte de esa pasión me gustaría compartir lo poco/mucho que sé con ustedes; como parte de esta misión, abri este repositorio para que ustedes suban códigos y podamos hacer code reviews sobre cualquier cosa que estén aprendiendo, en un ambiente que les servirá aprender para el futuro.

## ¿Cómo unirse al Coding Gym?

Envíame un correo a erosethanjv@gmail.com con tu nombre de usuario en GitHub y te agregare como contribuidor.

## ¿Cómo subo mi código al repositorio?

Hay algunos pasos a seguir antes de subir tus codigos aquí, pero una vez que los completes, hacerlos cambios en el futuro será muy fácil. Además, hacerlo aquí me permite controlar la calidad del código y quedará almacenado como referencia para ti y los demás.

### 1. Instala Git

Puedes hacerlo en https://git-scm.com/downloads.

### 2. Clona el repositorio

Abre una terminal y corre el siguiente comando para copiar los archivos del repositorio a tu computadora:

`git clone https://github.com/erosethan/coding-gym.git`

### 3. Crea tu propia rama en el repositorio

Crea tu propia rama en el repositorio, sientete libre de hacer tantos cambios como quieras en esa rama. Sin embargo, la rama principal `main` es la que consideraremos oficial para el repositorio, por lo que para integrar tus cambios a `main` necesitarás aprobación de un dueño del repositorio.

`git checkout -b user/nombre_de_usuario`

Por ejemplo: `git checkout -b user/erosethan`

### 4. Escribe tu código y haz commit

Antes de empezar a escribir tu código, obtén los últimos cambios del repositorio en tu rama. Esto incluirá todos los cambios que los demás y tú hayan hecho a la rama principal. Sin estos cambios, puede que estés viendo una versión anterior del repositorio.

`git pull origin main --rebase`

Asegurate de crear tu propia carpeta en el repositorio con tu nombre de usuario, en esa carpeta escribe cualquier código que quieras subir.

Checar cambios que haz hecho en la rama:
`git status`

Agregar un archivo especifico a tu commit:
`git add direccion_del_archivo`

Agregar todos los cambios al commit:
`git add -A`

Guardar los cambios del commit:
`git commit`

Guardar los cambios del commit con descripcion corta:
`git commit -m "Descripcion corta del commit"`

Tip: Intenta que la descripción de tus commits sea informativa y útil, es una buena práctica para que en el futuro seas un buen dev.

### 5. Sube tus cambios al repositorio

Cuando termines de escribir tu código, ejecuta el comando `git push` para subirlo al repositorio.

### 6. Crea un pull request y obtén aprobación

Si bien, en un concurso es válido programar de manera rápida, en este repositorio mantendremos un nivel mínimo de calidad en el código. Esto quiere decir que no permitiremos nombres de variables o métodos poco descriptivos y los comentarios informativos son súper bienvenidos.
