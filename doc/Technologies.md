# AvS Technology

* [MQTT Mosquitto Broker](http://mosquitto.org/)
  * höchst stable, kann mit jeder Sprache benutzt werden
* [Travis CI](https://travis-ci.org/) Continuous Integration Server

## C/C++

* [Lua](http://www.lua.org/) embedded scripting
  * [LuaBridge](https://github.com/vinniefalco/LuaBridge) for easy OO Lua bindings
* MQTT
  * [libmosquitto](http://mosquitto.org/)
* JSON config/data files
  * [JsonCpp](https://github.com/open-source-parsers/jsoncpp)
  * [rapidjson](https://github.com/miloyip/rapidjson)

* [CMake](https://cmake.org/)
* Makefile
* [Omniorb](http://omniorb.sourceforge.net/) CORBA Orb

### Anmerkung

Manuelles memory management. Viele Bibliotheken und große Community. Arbeit mit gcc oder clang. Gcc unter OSX muss ausprobiert werden. Wird in Maschinencode übersetzt, daher schnelle Ausführung. Komplexe und umständliche Sprache.

## C\#

* [Mono](http://www.mono-project.com/) crossplatform .NET runtime
* MQTT
  * [M2Mqtt](https://code.msdn.microsoft.com/windowsapps/M2Mqtt-MQTT-client-library-ac6d3858) .NET only, Mono compatability to be tested
* JSON config/data files
  * [JSON .Net](http://www.newtonsoft.com/json)
  * [fastJSON](http://www.codeproject.com/Articles/159450/fastJSON)
* [CMake](https://cmake.org/)
  * [CMake + C#](https://cmake.org/pipermail/cmake/2012-August/051691.html)
* Makefile
* [Remote Objects in .NET](http://www.jot.fm/issues/issue_2004_01/column8/)
* [Distribted Computing C#](http://stackoverflow.com/questions/6981358/distributed-computing-in-c-sharp)

### Anmerkung

Könnte etwas komplizierter werden, da C# eigentich eine .NET Sprache. Alle Bibliotheken sind für .NET geschrieben. Kompatibilität mit Mono ist nicht zu 100% gegeben und muss erst selbst herausgefunden werden. Community bezieht sich hauptsächlich auf .NET, weniger auf Mono. Aufwand zur Entwicklung unter Mono nicht abschätzbar.

## Python

* Builtin JSON parser
* [Paho MQTT](http://git.eclipse.org/c/paho/org.eclipse.paho.mqtt.python.git/)
* [ICE RPC Framework](https://zeroc.com/)
* [OmniorbPy](http://omniorb.sourceforge.net/) CORBA Orb
* [Distributed Programming](https://wiki.python.org/moin/DistributedProgramming)
* [Pylint Codeanalyser](https://pypi.python.org/pypi/pylint)

### Anmerkung

Könnte evtl. langsam sein, da Scriptsprache. Außerdem dynamisch typisiert, was zu vielen Laufzeitfehlern führen könnte. Daher unbedingt Codeanalyser wie Pylint benutzen. Einfache Programmierung und viel Community support. Extrem viele Bibliotheken und Frameworks.
