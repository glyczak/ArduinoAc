/*
Arduino Ethernet Script Server
Created Mars 4, 2014
Mikael Kindborg, Evothings AB
TCP socket server that accept commands for basic scripting
of the Arduino board.
This example is written for use with an Ethernet shield.
The API consists of the requests listed below.
Requests and responses end with a new line.
The input parameter n is a pin number ranging from 2 to 9.
The response is always a 4-character string with a
hex encoded number ranging from 0 to FFFF.
Possible response string values:
H (result from digital read)
L (result from digital read)
0 to 1023 - Analog value (result from analog read)
Set pin mode to OUTPUT for pin n: On
Response: None
Example: O5
Note: O is upper case letter o, not digit zero (0).
Set pin mode to INPUT for pin n: In
Response: None
Example: I5
Write LOW to pin n: Ln
Response: None
Example: L5
Write HIGH to pin n: Hn
Response: None
Example: H5
READ pin n: Rn
Response: "H" (HIGH) or "L" (LOW)
Example: R5 -> H
ANALOG read pin n: An
Response: int value as string (range "0" to "1023")
Example: A5 -> 42
*/

// Include files.
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below, usually found on a sticker
// on the back of your Ethernet shield.
byte mac[] = { 0x98, 0x4F, 0xFF, 0x01, 0x9B, 0x6F };

// The IP address will be dependent on your local network.
// If you have IP network info, uncomment the lines starting
// with IPAddress and enter relevant data for your network.
// If you don't know, you probably have dynamically allocated IP adresses, then
// you don't need to do anything, move along.
IPAddress ip(192,168,1, 9);
IPAddress gateway(192,168,1, 1);
IPAddress subnet(255, 255, 255, 0);

// Create a server listening on the given port.
EthernetServer server(3300);

void setup()
{
	pinMode(8, OUTPUT);

	Serial.begin(9600);

	// Wait for serial port to connect. Needed for Leonardo only.
	while (!Serial) { ; }

    Ethernet.begin(mac, ip, gateway, subnet);

	// Start the server.
	server.begin();

	// Print status.
	printServerStatus();
}

void loop()
{
	// Listen for incoming client requests.
	EthernetClient client = server.available();
	if (!client)
	{
		return;
	}

	Serial.println("Client connected");

	String request = readRequest(&client);
	executeRequest(&client, &request);

	// Close the connection.
	//client.stop();

	Serial.println("Client disonnected");
}

// Read the request line,
String readRequest(EthernetClient* client)
{
	String request = "";

	// Loop while the client is connected.
	while (client->connected())
	{
		// Read available bytes.
		while (client->available())
		{
			// Read a byte.
			char c = client->read();

			// Print the value (for debugging).
			Serial.write(c);

			// Exit loop if end of line.
			if ('\n' == c)
			{
				return request;
			}

			// Add byte to request line.
			request += c;
		}
	}
	return request;
}

void executeRequest(EthernetClient* client, String* request)
{
	if(request->equals("T"))
	{
		digitalWrite(8, HIGH);
		delay(100);
		digitalWrite(8, LOW);
	}
}

void printServerStatus()
{
	Serial.print("Server address:");
	Serial.println(Ethernet.localIP());
}
