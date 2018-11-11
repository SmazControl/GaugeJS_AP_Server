#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <FS.h> // Include the SPIFFS library

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);
String message = "";
int count = 0;

String getContentType(String filename) { // convert the file extension to the MIME type
if (filename.endsWith(".html")) return "text/html";
else if (filename.endsWith(".css")) return "text/css";
else if (filename.endsWith(".js")) return "application/javascript";
else if (filename.endsWith(".ico")) return "image/x-icon";
else if (filename.endsWith(".woff2")) return "font/woff2";
return "text/plain";
}

bool handleFileRead(String path) { // send the right file to the client (if it exists)
Serial.println("handleFileRead: " + path);
if (path.endsWith("/")) path += "index.html"; // If a folder is requested, send the index file
String contentType = getContentType(path); // Get the MIME type
if (SPIFFS.exists(path)) { // If the file exists
File file = SPIFFS.open(path, "r"); // Open it
size_t sent = webServer.streamFile(file, contentType); // And send it to the client
file.close(); // Then close the file again
return true;
}
Serial.println("\tFile Not Found");
return false; // If the file doesn't exist, return false
}

void handleRoot() {

// Arduino need "" for String OMG!!
String ux = "<!DOCTYPE html>";
ux=ux+"<html>";
ux=ux+"    <head>";
ux=ux+"<!--Import Google Icon Font-->";
ux=ux+"      <link href='font.css' rel='stylesheet'>";
ux=ux+"      <!--Import materialize.css-->";
ux=ux+"      <link type='text/css' rel='stylesheet' href='materialize.min.css'  media='screen,projection'/>";
ux=ux+"      <!--Let browser know website is optimized for mobile-->";
ux=ux+"      <meta name='viewport' content='width=device-width, initial-scale=1.0'/>";
ux=ux+"    </head>";
ux=ux+"    <body>";
ux=ux+"      <!--JavaScript at end of body for optimized loading-->";
ux=ux+"      <script type='text/javascript' src='materialize.min.js'></script>";
ux=ux+"    <div class='row grey darken-3'>";
ux=ux+"      <!--Top Pane -->";
ux=ux+"      <div class='col s12'>";
ux=ux+"        <a class='waves-effect waves-light btn-large red'>Power</a>";
ux=ux+"        <a class='waves-effect waves-light btn-large'>Button 2</a>";
ux=ux+"        <a class='waves-effect waves-light btn-large'>Button 3</a>";
ux=ux+"        <a class='waves-effect waves-light btn-large'>Button 4</a>";
ux=ux+"        <a class='waves-effect waves-light btn-large'><i class='material-icons right'>cloud</i>Button</a>";
ux=ux+"      </div>";
ux=ux+"      <!--Left Pane -->";
ux=ux+"      <div class='col s7'>";
ux=ux+"      <div class='collection'>";
ux=ux+"        <a href='#!' class='collection-item black'><span class='badge'>12.25 Km/L</span>1 Check</a>";
ux=ux+"        <a href='#!' class='collection-item black'><span class='new badge'>4</span>2 Notify</a>";
ux=ux+"        <a href='/count?count=1&speed=120' class='collection-item black'><span class='badge'>"+count+"</span>3 Play Count</a>";
ux=ux+"        <a href='#!' class='collection-item black'>4 Stop</a>";
ux=ux+"        <a href='#!' class='collection-item black'>5 Forward</a>";
ux=ux+"        <a href='#!' class='collection-item black'>6 Reverse</a>";
ux=ux+"        <a href='#!' class='collection-item black'><span class='badge'>14</span>7 Playlists</a>";
ux=ux+"      </div>";
ux=ux+"      </div>";
ux=ux+"      <!--Right Pane -->";
ux=ux+"      <div class='col s5'><br>";
ux=ux+"        <a href='#!'><i class='large material-icons'>insert_chart</i></a>";
ux=ux+"        <a href='#!'><i class='large material-icons'>apps</i></a>";
ux=ux+"        <a href='#!'><i class='large material-icons'>archive</i></a><br>";
ux=ux+"        <a href='#!'><i class='large material-icons'>arrow_upward</i></a>";
ux=ux+"        <a href='#!'><i class='large material-icons'>all_inclusive</i></a>";
ux=ux+"        <a href='#!'><i class='large material-icons'>audiotrack</i></a><br>";
ux=ux+"        <a href='#!'><i class='large material-icons'>arrow_downward</i></a>";
ux=ux+"        <a href='#!'><i class='large material-icons'>backup</i></a>";
ux=ux+"        <a href='#!'><i class='large material-icons'>bluetooth</i></a><br>";
ux=ux+"      </div>";
ux=ux+"    </div>";
// Message from parameter
ux += message;
// Gauge part for GaugeJS Demo
ux += "<script type='text/javascript' src='/gauge.min.js'></script>";
ux += "<canvas id='foo' width=250 height=210></canvas>";
ux += "<label id='gauge-value'></label>";
ux += "<script type='text/javascript'>";
ux += "var opts = {";
ux += " fontSize: 14,";
ux += " angle: -0.2,";
ux += " lineWidth: 0.2,";
ux += " radiusScale: 1,";
ux += " pointer: {";
ux += " length: 0.6,";
ux += " strokeWidth: 0.035,";
ux += " color: '#000000'";
ux += " },";
ux += " limitMax: false,";
ux += " limitMin: false,";
ux += " colorStart: '#6FADCF',";
ux += " colorStop: '#8FC0DA',";
ux += " strokeColor: '#E0E0E0',";
ux += " generateGradient: true,";
ux += " highDpiSupport: true,"; 
ux += " staticLabels: {";
ux += " font: '14px sans-serif',";
ux += " labels: [200, 500, 1000, 1500, 2000, 3000],";
ux += " color: '#000000',";
ux += " fractionDigits: 0";
ux += " },";
ux += " staticZones: [";
ux += " {strokeStyle: '#F03E3E', min: 200, max: 500, height: 1.4},";
ux += " {strokeStyle: '#FFDD00', min: 500, max: 1000, height: 1.2},";
ux += " {strokeStyle: '#30B32D', min: 1000, max: 1500, height: 1.0},";
ux += " {strokeStyle: '#FFDD00', min: 1500, max: 2000, height: 0.8},";
ux += " {strokeStyle: '#F03E3E', min: 2000, max: 3000, height: 0.6},";
ux += " {strokeStyle: 'rgb(80,80,80)', min: 2470, max: 2530, height: 1.3}";
ux += " ],";
ux += "}; ";
ux += "var target = document.getElementById('foo');";
ux += "var gauge = new Gauge(target).setOptions(opts);";
ux += "percentColors = [[0.0, '#a9d70b' ], [0.50, '#f9c802'], [1.0, '#ff0000']];";
ux += "gauge.maxValue = 3000;";
ux += "gauge.setMinValue(0);";
ux += "gauge.animationSpeed = 32;";
ux += "gauge.set(1250);";
ux += "gauge.setTextField(document.getElementById('gauge-value'));";
ux += "</script>";
ux += "</body>";
ux += "</html>";

webServer.send(200, "text/html", ux); 
}

void handleNotFound(){
if (!handleFileRead(webServer.uri())) { // send it if it exists
String message = "Hello World!\n\n";
message += "URI: ";
message += webServer.uri();

webServer.send(200, "text/plain", message);
}
}

void setup() {
WiFi.mode(WIFI_AP);
WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
WiFi.softAP("DNSServer example");

// modify TTL associated with the domain name (in seconds)
// default is 60 seconds
dnsServer.setTTL(300);
// set which return code will be used for all other domains (e.g. sending
// ServerFailure instead of NonExistentDomain will reduce number of queries
// sent by clients)
// default is DNSReplyCode::NonExistentDomain
dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);

// start DNS server for a specific domain name
dnsServer.start(DNS_PORT, "www.example.com", apIP);

// simple HTTP server to see that DNS server is working
webServer.on("/", handleRoot); 
webServer.on("/count", handleGenericArgs);
webServer.onNotFound(handleNotFound);
SPIFFS.begin(); 
webServer.begin();
}

void loop() {
dnsServer.processNextRequest();
webServer.handleClient();
}


void handleGenericArgs() { //Handler

  message = "<div>Number of args received:";
  message += webServer.args();            //Get number of parameters
  message += "</div>";                            //Add a new line

  for (int i = 0; i < webServer.args(); i++) {

    message += "<div>Arg number#" + (String)i + " > ";   //Include the current iteration value
    message += webServer.argName(i) + ": ";     //Get the name of the parameter
    message += webServer.arg(i) + "</div>";              //Get the value of the parameter
    if (webServer.argName(i) == "count") {
      count = count + webServer.arg(i).toInt(); 
    }
  }
  handleRoot();
}
