/** HTTP POST Beispiel
*/
#include "mbed.h"
#include "HTTPClient.h"
#include "data/HTTPText.h"
#include "EthernetInterface.h"

EthernetInterface eth;
// HTTPClient Hilfsklasse
HTTPClient http;
// I/O Buffer
char str[512];

DigitalOut myled(LED1);

int main()
{
    printf("HTTP Client - POST\n");
    eth.init();
    eth.connect();

    while(1) 
    {
        myled = 1;

        // Hilfsklasse um die Response vom Server zu formatieren     
        HTTPText inText(str, 512);
        
        // MAP (Argument=Wert) 
        HTTPMap map;
        map.put("DigitalOut", "LED1");
        map.put("write", "1");
        
        int ret = http.post("http://httpbin.org/post", map, &inText);
        // lokale Variante mit CGI-Script auf IoT USB Stick. Wenn nicht Funktioniert: iot-stick durch IP-Adresse ersetzen
        // int ret = http.post("http://iot-stick/rest/cgi-bin/rest", map, &inText);
        if ( ! ret ) 
        {
            printf("Executed POST successfully - read %d characters\n", strlen(str));
            printf("Result: %s\n", str);
        } 
        else 
        {
            printf("Error - ret = %d - HTTP return code = %d\n", ret, http.getHTTPResponseCode());
        }
        
        myled = 0;

        wait(10);
    }
    //eth.disconnect();
} 
