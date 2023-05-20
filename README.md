Pentru rezolvarea temei am folosit mai multe clase.

Clasa Request are ca fielduri toate datele de care ar putea avea nevoie un request.
Functia compute_request ia datele din field uri si genereaza un string cu request-ul corespunzator.

Pentru a putea crea cu usurinta un request nou am folosit Builder Pattern.
Avem clasa RequestBuilder care ne permite sa cream cu usurinta Obieacte
de tip Request.
Astfel putem genera un request asa: 
        string req= RequestBuilder()
                .setType("POST")
                .setHost(ip)
                .setUrl("/api/v1/tema/auth/login")
                .setContentType("application/json")
                .setLogin(login)
                .setPassword(pass)
                .build()
                .get_request();

In clasa Helpers avem niste functii statice care ne ajuta la comunicarea cu serverul. Majoritatea functiilor de aici sunt luate din laboratorul 9.

Pentru parsarea de JSON uri am folosit biblioteca nlohmann/json. Pentru a o folosi
am inclus in proiect fisierul json.hpp din directorul include/nlohmann.

Clasa Client implementeaza toate comenzile pe care le poate trimite clientul catre 
server.