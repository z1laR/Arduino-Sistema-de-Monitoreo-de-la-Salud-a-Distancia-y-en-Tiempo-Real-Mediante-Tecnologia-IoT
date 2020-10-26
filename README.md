<p align="center"><img src="https://sites.google.com/site/ecoblockitsjr2012/_/rsrc/1467088772182/general-information/la-empresa/Logo_ITSJR_-_Completo.jpg?height=282&width=264"></p>

<p align="center"><b>Tecnológico Nacional de México</b></p>

<p align="center"><b>Instituto Tecnológico de San Juan del Río</b></p>

<p align="center"><b>Ingeniería en Sistemas Computacionales</b></p>

<p align="center"><b>SISTEMA DE MONITOREO DE LA SALUD A DISTANCIA <br> Y EN TIEMPO REAL MEDIANTE TECNOLOGÍA IOT</b></p>

<p align="center"><b>P R E S E N T A:</b></p>

<p align="center">Omar Mancilla Pérez</p>
<p align="center">N° Control 13590623</p>

<p align="center">A S E S O R E S:</p>
<p align="center">Dra. Armida González Lorence</p>
<p align="center">Dr. José Gabriel Ayala Landeros</p>
<p align="center">ME. Angélica Jacqueline Amaya Pérez</p>
<p align="center">Ing. Govani Gregorio Sánchez Orduña</p>
<p align="center">Lic. Sonia Elizabeth Román Flores</p>

<p align="justify">En este repositorio se encuentra el programa en Arduino complementario al presente proyecto de investigación con el cual se podrán calcular y enviar los datos referentes a los sensores que estarán
en todo momento monitoreando los signos vitales (pulso cardiaco/electrocardiograma, temperatura corporal y saturación de oxígeno en la sangre) de pacientes que se encuentren en reposo desde su hogar.

<p align="center">© 2019 - 2020 | Todos los derechos reservados | Hecho de ♥ por <a href="https://www.itsanjuan.edu.mx" target="_blank">ITSJR Research</a> & <a href="https://www.omar-mancilla.tech" target="_blank">Omar Mancilla</a></p>

<h1>Diagrama de conexión</h1>

<a href="https://imgur.com/qirui79"><img src="https://i.imgur.com/qirui79.png" title="source: imgur.com" /></a>

<h1>Configuración de IP (asignación manual / DHCP)</h1>

<p>Primeramente, si deseas asignar una IP a tu placa Arduino necesitarás también de una dirección MAC para evitar que Arduino NO la reconozca. La dirección que elijas no debe de estar en uso por algún otro dispositivo de tu red de lo contrario podrían existir colisiones, o peor aún, ataques <b>MAC spoofing</b>.</p>

<p>Puedes dejar la que viene en el programa por defecto:</p>
<pre>byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };</pre>

<p>Ahora bien, para asignar de forma manual solo tendrás que seleccionar la IP, reemplazarla y descomentar las lineas:</p>

<pre>
byte ip[] = { 192, 168, 0, 102 };
Ethernet.begin(mac, ip, gateway, subnet);
</pre>

Y agregar comentarios a:

<pre>
//Ethernet.begin(mac, gateway, subnet);
//client.dhcp();
//Serial.println(Ethernet.localIP());
</pre>

Si prefieres que tu router por medio de DHCP lo haga no tendrás que modificar algo, el programa lo realiza de forma automática :D

<h1>Bilbiotecas</h1>

El programa se escribio haciendo uso de las siguientes bibliotecas, es posible que actualmente ya presenten actualizaciones con mejoras significativas que podrían dejar obsoleto a este repositorio, esto no depende de mi, si no de los desarrolladores que dan soporte individual a cada una.

<ul>
  <li><b>ArduinoJson</b> by Benoit Blanchon <i>Versión 5.13.3</i></li>
  <li><b>DallasTemperature</b> by Miles Burton, Tim Newsome, Guil Barros and Rob Tillaart <i>Versión 3.8.0</i></li>
  <li><b>PulseSensor Playground</b> by Joel Murphy, Yury Gitman and Brad Needham <i>Versión 1.5.1</i></li>
  <li><b>MAX30100</b> by Connor Huffine <i>Versión 1.0.0</i></li>
  <li><b>MAX30100lib</b> by OXullo Intersecans <i>Versión 1.1.0</i></li>
  <li><b>OneWire</b> by Jim Studt, Tom Pollard, Robin James ... <i>Versión 2.3.5</i></li>
  <li><b><a href="https://github.com/csquared/arduino-restclient">arduino-restclient-master</a></b> by Chris Continanza and James Ward <i>Versión desconocida</i></li>
</ul>

<h1>Circuito final</h1>

<a href="https://imgur.com/7dwghmL"><img src="https://i.imgur.com/7dwghmL.jpg" title="source: imgur.com" /></a>
