/*#include <iostream> // cerr, cout, endl

#include "../include/Cgi.hpp"
#include "../include/Request.hpp"
#include "../include/Response.hpp"

int main()
{
    try
    {
        Request req;

        std::string rawRequest = "GET /cgi-bin/script.py?user=admin HTTP/1.1\r\n"
                                 "Host: localhost\r\n"
                                 "Content-Type: text/plain\r\n"
                                 "Content-Length: 22\r\n"
                                 "\r\n"
                                 "Testing GET method...";

        // 2. Alimentamos al req
        req.feed(rawRequest);

        if (req.hasError()) {
            std::cerr << "Error en el parseo: " << req.errorCode() << std::endl;
            return 1;
        }

        if (req.isComplete()) {
            // 3. Obtenemos la HttpRequest resultante (que es const)
            const Request& req = req.get();

            // 4. Ejecutamos el CGI
            // Asegúrate de que "test.py" existe en tu carpeta actual
            std::string scriptPath = "www/cgi-bin/script.py";
            Response res = Cgi::handleCgi(req, scriptPath);

            // 5. Mostramos el resultado
            std::cout << "--- CGI OUTPUT ---" << std::endl;
            std::cout << "Status: " << res.getStatusCode() << std::endl;
            std::cout << "Body: " << res.getMessageBody() << std::endl;
        } else {
            std::cerr << "La petición no está completa (faltan datos)" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Excepción: " << e.what() << std::endl;
    }

    return 0;
}*/
