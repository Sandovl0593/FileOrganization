<a name="readme-top"></a>

<div align="center">
  <a href="https://https://github.com/Auky216/Cachimbo">
  </a>
  <h1>File Organization</h1>
</div>
<h3 align="center">Base de Datos II - Proyecto 01</h3>

## Integrantes

- Espinoza Herrera, Marcela
- Sandoval Huamaní, Adrian
- Guillén Rodriguez, Fernando
- Lindo Peña, Ximena Nicolle

## Introducción

### Objetivo del Proyecto:

El objetivo de nuestro proyecto fue mejorar significativamente la eficiencia en la búsqueda y gestión de registros en memoria secundaria. Para lograr esto, nos enfocamos en los siguientes aspectos clave:

- Implementación de Estructuras de Datos: Utilizamos técnicas avanzadas como Sequential File, ISAM-Sparse Index y Extendible Hashing para estructurar los archivos. Esto nos permitió optimizar las búsquedas y garantizar accesos más rápidos y eficientes.

- Desarrollo de Algoritmos de Búsqueda: Implementamos algoritmos de búsqueda avanzados que optimizan el tiempo de ejecución durante el acceso a los datos. Estos algoritmos están diseñados para integrarse y aprovechar al máximo las estructuras de datos empleadas, mejorando significativamente la eficiencia en las operaciones de búsqueda y manipulación de datos.

- Optimización de Consultas SQL: Integrando un parser de SQL que trabaja directamente con nuestras estructuras de datos, conseguimos que las consultas SQL sean más eficaces. Este parser facilita la ejecución de consultas complejas, mejorando la interacción con los datos y la realización de operaciones básicas como inserción y eliminación.

Estas iniciativas nos permitieron no solo mejorar la gestión de los datos en nuestros proyectos, sino también obtener resultados más efectivos y eficientes en tiempo real.



### Descripción del Dominio de Datos Utilizados

Para este proyecto, seleccionamos el conjunto de datos de la **NBA Database** disponible en [Kaggle](https://www.kaggle.com/datasets/wyattowalsh/basketball). Este dataset proporciona información exhaustiva sobre jugadores y partidos de la NBA. Optamos por trabajar con dos archivos CSV específicos que son esenciales para nuestro proyecto:

**1. Información Común de los Jugadores (`common_player_info.csv`):**
El primer archivo contiene detalles sobre los jugadores, incluyendo identificaciones, nombres, fechas de nacimiento, escuelas, países, y más. Específicamente, el archivo incluye 4,172 filas y 16 columnas, con los siguientes campos:

- `person_id`: Identificación única del jugador (tipo `double`).
- `display_first_last`: Nombre completo del jugador (tipo `char[24]`).
- `birthdate`: Fecha de nacimiento (tipo `char[10]`).
- `school`: Escuela o universidad (tipo `char[31]`).
- `country`: País de origen (tipo `char[24]`).
- `height`: Altura (tipo `char[4]`).
- `weight`: Peso (tipo `double`).
- `season_exp`: Experiencia en temporadas (tipo `double`).
- `jersey`: Número de camiseta (tipo `char[7]`).
- `position`: Posición en el juego (tipo `char[14]`).
- `team_id`: Identificación del equipo (tipo `double`).
- `team_name`: Nombre del equipo (tipo `char[13]`).
- `team_abbreviation`: Abreviatura del equipo (tipo `char[3]`).
- `team_city`: Ciudad del equipo (tipo `char[25]`).
- `from_year`: Año de inicio en la NBA (tipo `double`).
- `to_year`: Último año en la NBA (tipo `double`).

**2. Información de Partidos (`game.csv`):**
El segundo archivo registra los partidos jugados en la liga durante los últimos 5 años, incluyendo información sobre equipos, fechas, y resultados. Contiene 7,213 filas y 16 columnas, con campos como:

- `season_id`: Identificación de la temporada (tipo `double`).
- `team_id_home`: Identificación del equipo local (tipo `double`).
- `team_abbreviation_home`: Abreviatura del equipo local (tipo `char[3]`).
- `team_name_home`: Nombre del equipo local (tipo `char[22]`).
- `game_id`: Identificación del juego (tipo `double`).
- `game_date`: Fecha del juego (tipo `char[10]`).
- `matchup_home`: Enfrentamiento en casa (tipo `char[11]`).
- `pts_home`: Puntos anotados por el equipo local (tipo `double`).
- `plus_minus_home`: Diferencia de puntos del equipo local (tipo `double`).
- `team_id_away`: Identificación del equipo visitante (tipo `double`).
- `team_abbreviation_away`: Abreviatura del equipo visitante (tipo `char[3]`).
- `team_name_away`: Nombre del equipo visitante (tipo `char[25]`).
- `matchup_away`: Enfrentamiento fuera de casa (tipo `char[9]`).
- `pts_away`: Puntos anotados por el equipo visitante (tipo `double`).
- `plus_minus_away`: Diferencia de puntos del equipo visitante (tipo `double`).
- `season_type`: Tipo de temporada (tipo `char[14]`).

Cada archivo fue elegido por su relevancia y la riqueza de sus datos, que son cruciales para la implementación de nuestras técnicas de organización de archivos y para las pruebas de nuestras consultas y algoritmos de búsqueda.


### Resultados Esperados al Aplicar las Técnicas de Indexación

En este proyecto, nos proponemos evaluar y comparar el impacto de las técnicas de indexación en la gestión de datos en memoria secundaria. Con base en las implementaciones y pruebas realizadas, anticipamos los siguientes resultados:

- **Evaluación de Rendimiento:** Mediante pruebas controladas, determinaremos el rendimiento de cada técnica de indexación observando aspectos críticos como los tiempos de ejecución y los accesos al disco duro. Esto nos ayudará a identificar la técnica más efectiva para nuestro contexto de uso.

- **Optimización de Acceso a Datos:** Esperamos que las técnicas de indexación permitan una reducción significativa en la cantidad de accesos a la memoria secundaria, optimizando así el proceso de consulta de datos.

- **Eficiencia en Operaciones de Datos:** Mediante el uso de estructuras de datos especializadas, buscamos mejorar la eficiencia de operaciones fundamentales como la inserción, búsqueda, recuperación y eliminación de registros.

- **Comparación entre Estructuras:** Estableceremos cuál de las estructuras de datos implementadas demuestra mayor eficacia en términos de tiempo de ejecución y manejo de grandes volúmenes de información.

- **Organización de Datos:** A través de estas técnicas, también pretendemos mejorar la organización de los registros dentro de la memoria secundaria, facilitando una recuperación más rápida y una gestión más eficiente del espacio de almacenamiento.

Con estos resultados, buscamos no solo validar la aplicabilidad de las técnicas aprendidas en clase, sino también demostrar su utilidad en escenarios reales de manejo de datos a gran escala.



## Tecnicas Utilizadas


### Sequential File
El **Sequential File** emplea una estructura de datos lineal que facilita el acceso secuencial a los registros. Este método utiliza dos archivos: uno principal para los datos regulares y otro auxiliar para manejar inserciones excepcionales o temporales. Los registros en el archivo principal están ordenados, lo que permite búsquedas eficientes.

#### Inserción:
La inserción en el archivo secuencial depende de la posición relativa del nuevo registro respecto a los existentes, basándose en la clave primaria:

1. **Verificación del Orden:** Si el nuevo registro tiene una clave mayor que cualquier registro existente en el archivo principal, se añade al final de este archivo.
2. **Archivo Auxiliar:** Si el nuevo registro no sigue el orden secuencial, se inserta en el archivo auxiliar.
3. **Actualización de Punteros:** Independientemente de su ubicación, los punteros asociados deben actualizarse para reflejar la nueva entrada.
4. **Reorganización del Archivo Auxiliar:** Cuando el archivo auxiliar alcanza su capacidad máxima, se realiza una reorganización para integrar estos registros al archivo principal, manteniendo el orden.

#### Búsqueda:
La eficacia de la búsqueda depende del archivo en el que se almacene el registro:

1. **Búsqueda Binaria en Archivo Principal:** Se utiliza una búsqueda binaria para encontrar registros rápidamente gracias al orden secuencial.
2. **Escaneo del Archivo Auxiliar:** Si la búsqueda en el archivo principal falla, se recorre el archivo auxiliar de manera secuencial.
3. **Búsqueda por Rango:** Inicia desde el primer registro del archivo principal y continua agregando registros que cumplan con las condiciones especificadas hasta que se encuentre uno que no lo haga.

#### Eliminación:
La eliminación requiere una cuidadosa gestión de punteros para mantener la integridad de la estructura de datos:

1. **Localización del Registro:** Identificar el registro a eliminar por su clave y determinar sus registros predecesor y sucesor.
2. **Actualización de Punteros:** El puntero del registro eliminado se ajusta para reflejar su eliminación, comúnmente configurándolo a un valor especial que indica que está vacío o inactivo.
3. **Mantenimiento del Orden:** Asegurar que los punteros en los registros adyacentes se actualicen para mantener el acceso secuencial coherente.

### ISAM
El **ISAM** es una técnica de organización de archivos que combina el acceso secuencial con un método de indexación para mejorar el rendimiento en entornos de memoria secundaria. Utiliza un archivo de datos principal donde los registros están ordenados, y un archivo de índice que permite accesos rápidos a los datos a través de claves indexadas.

#### Inserción:
La inserción en ISAM sigue un proceso estructurado para mantener la eficiencia del índice:

1. **Localización del Punto de Inserción:** Utilizando el índice, se determina la posición adecuada en el archivo de datos donde el registro debe ser insertado para mantener el orden.
2. **Inserción en el Archivo de Datos:** Si hay espacio suficiente en la página de datos, el registro se inserta directamente. Si no, se procede a una división de página.
3. **Actualización del Índice:** Cada inserción puede requerir una actualización del archivo de índice para reflejar la nueva entrada y mantener la integridad de los punteros.
4. **Manejo de Páginas de Overflow:** Si la inserción en la ubicación adecuada no es posible debido al espacio, se utiliza una página de overflow.

#### Búsqueda:
ISAM optimiza las búsquedas utilizando el índice para acceder directamente a los datos:

1. **Búsqueda en el Índice:** Se realiza una búsqueda binaria en el archivo de índice para localizar la página de datos que contiene la clave buscada.
2. **Acceso Directo a los Datos:** Una vez identificada la página, se accede directamente a ella y se realiza una búsqueda secuencial en esa página para encontrar el registro específico.
3. **Manejo de Páginas de Overflow:** Si el registro no se encuentra en la página principal, se busca en las páginas de overflow asociadas.

#### Eliminación:
La eliminación en ISAM debe gestionar adecuadamente tanto el archivo de datos como el índice:

1. **Búsqueda del Registro:** Utilizando el índice, se localiza la página de datos donde debería estar el registro.
2. **Eliminación del Registro:** El registro se elimina de la página de datos. Si es necesario, se ajustan los registros en la página para llenar el espacio vacío.
3. **Actualización del Índice:** Se actualiza el índice para reflejar la eliminación del registro.
4. **Compresión de Páginas:** Si la eliminación deja una página de datos suficientemente vacía, se puede considerar la compresión de páginas para optimizar el espacio.




### Extendible Hashing
El **Extendible Hashing** se caracteriza por su capacidad para gestionar datos de manera eficiente y adaptativa mediante directorios y buckets. Este método se ajusta dinámicamente a los cambios en los requisitos de almacenamiento, lo que permite la modificación de su estructura de índices y almacenamiento sin sacrificar el rendimiento en las operaciones de búsqueda, inserción o eliminación. La función hash en este sistema es especialmente útil para realizar búsquedas de igualdad de manera rápida y directa. Sin embargo, es importante señalar que, mientras es excelente para estas búsquedas puntuales, el extendible hashing no está optimizado para búsquedas por rango, debido a que la distribución de los datos en buckets no preserva un orden específico que facilite este tipo de consultas.
#### Inserción:
Para insertar un elemento en el extendible hashing, se deben seguir los siguientes pasos:
1. Cálculo del Valor Binario:
   Se calcula el valor binario del atributo clave que determinará la posición en el extendible hashing.
2. Evaluación de la Profundidad del Bucket:
   Se evalúa la profundidad local del bucket correspondiente. Por ejemplo, si el valor binario es '101001' y la profundidad del bucket es 3, la función hash utilizará los tres primeros dígitos del binario, '101', para ubicar el bucket adecuado.

![Estructura de Hashing Dinámico](https://media.discordapp.net/attachments/1015053042959265802/1241790795644928130/image.png?ex=664b7b4d&is=664a29cd&hm=14c5418f95cc19153c6181427dd2d384d8a42cf5568734a5c2bbbcc341fc3dc6&=&format=webp&quality=lossless&width=565&height=417)

3. Guía de Inserción en la Estructura del Árbol:
   La inserción se guía por la estructura de un árbol digital, donde se inserta a la izquierda si el dígito relevante es 0 y a la derecha si es 1. Esto posiciona al bucket en una ubicación específica dentro de la estructura del árbol, funcionando como una hoja.

![Overflow](https://media.discordapp.net/attachments/1015053042959265802/1241791093507620915/image.png?ex=664b7b94&is=664a2a14&hm=49be5afa89c356b506db6f198bb795abe29089478fba64fdf713951995fa20e8&=&format=webp&quality=lossless&width=542&height=417
)

4. Verificación y Manejo de Desbordamiento:
   Se verifica si el bucket está lleno, lo que puede requerir una división. En caso de desbordamiento y si se ha alcanzado la profundidad global máxima, se creará un nuevo bucket incrementando la profundidad local y redistribuyendo los registros entre el nuevo y el antiguo bucket, repartiendo los datos equitativamente entre ambos.

![Redistribuir](https://media.discordapp.net/attachments/1015053042959265802/1241791520907198544/image.png?ex=664b7bf9&is=664a2a79&hm=9ca2280cfdecbd3ad9f2ca6f364031e5d95255e0b0b13da85374657bf5b70bf8&=&format=webp&quality=lossless&width=529&height=417)


#### Búsqueda:

El proceso de búsqueda en Extendible Hashing comienza con el hashing de la llave de búsqueda para generar un valor binario. Este valor determina el bucket específico en el directorio donde potencialmente se encuentra el registro. El proceso es el siguiente:

1. **Hash de la Llave:** Se aplica la función hash a la llave para obtener un valor hash que será interpretado como un número binario.
2. **Localización del Bucket:** Utilizando los bits más significativos del valor hash, determinados por la profundidad global del directorio, se identifica el bucket que debe contener el registro.
3. **Búsqueda en el Bucket:** Se busca directamente en el bucket especificado. Si el bucket tiene enlaces a buckets de desbordamiento debido a colisiones previas, la búsqueda se extiende a estos buckets adicionales.
4. **Resultado de la Búsqueda:** Si se encuentra el registro, se devuelve; de lo contrario, se devuelve un indicador, el cual especifica que no se encontró dicho registro.


#### Eliminación:
El proceso de eliminación en el Extendible Hashing involucra encontrar el registro deseado y luego removerlo del sistema. Los pasos a seguir para realizar este proceso son los siguientes:

1. **Hash de la Llave:** Al igual que en la búsqueda, la eliminación comienza con el hashing de la llave del registro que se desea eliminar, generando un valor hash interpretado como un número binario.
2. **Localización del Bucket:** Usando los bits más significativos del valor hash, y dependiendo de la profundidad global del directorio, se identifica el bucket donde teóricamente se encuentra el registro.
3. **Búsqueda en el Bucket:** Se examina el bucket identificado en busca del registro específico. Si hay buckets de desbordamiento asociados debido a colisiones, estos también se revisan para encontrar el registro.
4. **Eliminación del Registro:** Si se encuentra el registro, se elimina del bucket. Si el bucket queda vacío o con poca carga, se pueden considerar acciones adicionales como la fusión de buckets o la reorganización para mantener la eficiencia del hashing.
5. **Manejo de Desbordamientos:** Si se eliminan registros de un bucket de desbordamiento, se revisa si es posible simplificar la estructura eliminando el bucket de desbordamiento o redistribuyendo los registros restantes.
6. **Resultado de la Eliminación:** Se actualiza la estructura del directorio si es necesario, y se devuelve un indicador de éxito o fallo de la operación de eliminación.


## Análisis Comparativo (Respecto a los Accesos de Memoria Secundaria):

### Inserción:
- Sequiential File: O(n)
- ISAM: O(log n)
- Extendible Hashing: O(k)


Al analizar estas complejidades llegamos a la conclusión de que tanto el ISAM como el Extendible Hashing, son las mejores opciones para insertar registros. Esto se debe ya que, el Sequential File puede requerir reorganizaciones costosas cuando su archivo auxiliar se llena, un problema que ISAM y Extendible Hashing evitan mediante el uso eficiente de índices y división de buckets, respectivamente. Esto les permite manejar inserciones de manera más eficaz, especialmente bajo cargas elevadas.


### Búsqueda:
- Sequiential File: O(log n)
- ISAM: O(log n + k)
- Extendible Hashing: O(k)

Al comparar las complejidades de búsqueda, ISAM y Extendible Hashing proporcionan ventajas claras sobre Sequential File, especialmente en entornos donde las búsquedas son frecuentes y la eficiencia es crucial. ISAM, al emplear una mezcla de búsqueda binaria y secuencial (debido al componente "k"), ofrece una solución equilibrada entre rendimiento y simplicidad estructural. Extendible Hashing, con una complejidad de O(k) donde k es el número de operaciones en el bucket afectado, sobresale en escenarios donde la distribución de los datos es uniforme, permitiendo accesos extremadamente rápidos y directos.

### Eliminación:

- Sequiential File: O(n logn) + O(k)
- ISAM: O(n)
- Extendible Hashing: O(k)


En cuanto a eliminación, Extendible Hashing muestra una vez más su eficiencia con una complejidad de O(k), destacando en entornos donde las eliminaciones son tan críticas como las inserciones. Sequential File, aunque efectivo en mantener un orden, enfrenta desafíos significativos ya que cada eliminación puede requerir una reorganización completa, resultando en una complejidad más alta de O(n log n) más el coste de reubicación de otros elementos (O(k)). ISAM, por otro lado, aunque no es tan eficiente como Extendible Hashing, sigue siendo una mejor opción que Sequential File debido a su estructura más rígida y menor necesidad de reorganización completa.


Donde:

- k: Representa la cantidad de buckets en el overflow (en caso no exista, k=1)



## Parser SQL

### Descripción

Utilizamos la estrategia de [Crafting Interpreters](https://craftinginterpreters.com/parsing-expressions.html) de Robert Nystrom aplicada en C++ del **curso de Compiladores** como Parser para las consultas SQL. Está dividida en tres clases: Token, Scanner y Parser.

### Clase Token:

Empleamos palabras reservadas, signos y patrones o lexemas de una declaración SQL.

```c++
// palabras reservadas
CREATE, TABLE, INSERT, INTO, USING, INDEX, DELETE, ON,
SELECT, FROM, WHERE, FILE, VALUES,
HASH, ISAM, SEQ, AND, OR, BETWEEN, ALL
// signos
LPAREN, RPAREN, LESS, GREATER, LESSEQUAL,
GREATEREQUAL, EQUAL, COMMA, PTCOMMA,
// lexemas
STRING, ID, NUM, FLOAT,
// error o EOF
ERR, END
```

### Clase Scanner

Utilizamos una técnica intuitiva actualizando posiciones dentro de una cadena de entrada en un bucle en el método `nextToken()`, que finalmente identifica un Token:

```c++
if (c == '\'')
    // detecta cualquier carácter hasta que coincida con '\'' -> Token STRING
else if (c == '\"')
    // detecta cualquier carácter hasta que coincida con '\"' -> Token STRING
else if (isdigit(c))
    // detecta caracteres numéricos
    // si hay un punto, detecta más números -> Token FLOAT
    // caso contrario -> Token NUM
else if (isalpha(c) || c == '_')
    // detecta caracteres alfabéticos o '_'
    // si la subcadena leída es una palabra reservada -> Token [palabra]
    // caso contrario -> Token ID
else if (strchr("*(),;<>=", c)) {
    // para signos
    // algunos son de dos caracteres -> se leen ambos para un token
    // o caso contrario es otro token
else
    // error léxico
```

### Clase Parser

Utilizamos las siguientes sentencias SQL:

```
select ([atributos] | *) from [tabla];
select ([atributos] | *) from [tabla] where [k_atr] [>,<,>=,<=,=] [valor];
select ([atributos] | *) from [tabla] where [k_atr] between [inicio] and [fin];
create table [tabla] from file [nombre_archivo];
create index [id] on [tabla] using [tipo_indice]([atributo]);
insert into [tabla] values ([atributos]);
delete from [tabla] where [k_atr] = [valor];
```

Bajo estas sentencias, construimos una gramática para **reconocer y ejecutar** estas declaraciones de forma exitosa empleando métodos por cada regla de forma:

```c++
bool parseRegla() {
   if (!match(Token::[token])) {
      throw ParserError(/* error del parser */);
      return false;
   }
   // otras validaciones del parser
   // ...

   // extraemos los valores deseados
   // ejecuta la consulta
   bool execute = query(/* valores dependiendo de la regla */);

   if (!execute) return false; // validar la consulta
   return true;
}
```

La extracción de los valores se basa en lo siguiente:

- Si el Token es un signo de comparación, se almacena temporalmente con `previous->type` como parámetro para la búsqueda por rango.
- Se tienen dos objetos `unordered_map` con las tablas de Jugadores y Partidos donde almacena los pares *(atributo, índice)* donde índice puede ser `HASH`, `ISAM` o `SEQ`.
- Una `memoria` donde almacena los atributos, valores y la tabla necesarias para llamar a las consultas. Así, una vez leído correctamente por el parser, extraemos esos valores para proceder con la ejecución.


## Resultados Experimentales



## Pruebas de uso y Presentación

### Sequential con rebuild

![Sequentialconrebuild](https://media.discordapp.net/attachments/996002132891271188/1241975321650270318/Imagen_de_WhatsApp_2024-05-19_a_las_23.37.55_ed00901f.jpg?ex=664c2727&is=664ad5a7&hm=76e26cea9b132a8c24de57bcc2245ed9fc9690fe20316b0f7b12f94f83cb55ef&=&format=webp&width=472&height=417)




### Video Explicativo:

[Link del Video (subido en Drive)](https://drive.google.com/file/d/1T8S1XUJBudsWqLWfm1t5l9rvNHKbVprp/view?usp=sharing
)
