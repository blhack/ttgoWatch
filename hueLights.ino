void hueLightsOff() {
    String put_string;
    put_string = "{\"on\": false, \"hue\": 60632, \"sat\": 254, \"bri\": 10, \"xy\": [0.6815, 0.3014]}";
    int httpCode;
    HTTPClient http;

    String urlString;
    String payload;

    for (int i=4; i>0; i--) {
        urlString = "http://";
        urlString += HUEIP;
        urlString += "/api/";
        urlString += HUEUSER;
        urlString += "/lights/";
        urlString += String(i);
        urlString += "/state";
        for (int i=0; i<10; i++) {
            http.begin(urlString);
            http.addHeader("Content-Type", "application/json");
            Serial.println(urlString);
            http.setTimeout(1000);
            httpCode = http.PUT(put_string);
            Serial.println(httpCode);
            if (httpCode > 0) { //Check for the returning code
                payload = http.getString();
                Serial.println(payload);
                watch->tft->print("\n");
                watch->tft->print(httpCode);
                break;
            } 
            http.end();
        }
    }
}

void hueSleepyTime() {
    String put_string;
    put_string = "{\"on\": true, \"hue\": 60632, \"sat\": 254, \"bri\": 10, \"xy\": [0.6815, 0.3014]}";
    int httpCode;
    HTTPClient http;

    String urlString;
    String payload;

    for (int i=4; i>0; i--) {
        urlString = "http://";
        urlString += HUEIP;
        urlString += "/api/";
        urlString += HUEUSER;
        urlString += "/lights/";
        urlString += String(i);
        urlString += "/state";
        for (int i=0; i<10; i++) {
            http.begin(urlString);
            http.addHeader("Content-Type", "application/json");
            Serial.println(urlString);
            http.setTimeout(1000);
            httpCode = http.PUT(put_string);
            Serial.println(httpCode);
            if (httpCode > 0) { //Check for the returning code
                payload = http.getString();
                Serial.println(payload);
                watch->tft->print("\n");
                watch->tft->print(httpCode);
                break;
            } 
            http.end();
        }
    }
}


void hueLightsOn() {

    String put_string;
    put_string = "{\"on\": true, \"hue\": 65166, \"sat\": 254, \"bri\": 254, \"xy\": [0.4578, 0.41]}";
    int httpCode;
    HTTPClient http;
    String urlString;
    String payload;

    for (int i=4; i>0; i--) {
        urlString = "http://";
        urlString += HUEIP;
        urlString += "/api/";
        urlString += HUEUSER;
        urlString += "/lights/";
        urlString += String(i);
        urlString += "/state";
        for (int i=0; i<10; i++) {
            http.begin(urlString);
            Serial.println(urlString);
            http.addHeader("Content-Type", "application/json");
            http.setTimeout(1000);
            httpCode = http.PUT(put_string);
            Serial.println(httpCode);
            if (httpCode > 0) { //Check for the returning code
                payload = http.getString();
                Serial.println(payload);
                watch->tft->print("\n");
                watch->tft->print(httpCode);
                break;
            }
            http.end(); //Free the resources
        }
    }
}

void hueRedAlert() {

    String put_string;
    put_string = "{\"on\": true, \"hue\": 65166, \"sat\": 254, \"bri\": 254, \"xy\": [0.6815, 0.3014]}";
    int httpCode;
    HTTPClient http;
    String urlString;
    String payload;

    for (int i=4; i>0; i--) {
        urlString = "http://";
        urlString += HUEIP;
        urlString += "/api/";
        urlString += HUEUSER;
        urlString += "/lights/";
        urlString += String(i);
        urlString += "/state";
        for (int i=0; i<10; i++) {
            http.begin(urlString);
            Serial.println(urlString);
            http.addHeader("Content-Type", "application/json");
            http.setTimeout(1000);
            httpCode = http.PUT(put_string);
            Serial.println(httpCode);
            if (httpCode > 0) { //Check for the returning code
                payload = http.getString();
                Serial.println(payload);
                watch->tft->print("\n");
                watch->tft->print(httpCode);
                break;
            }
            http.end(); //Free the resources
        }
    }
}
