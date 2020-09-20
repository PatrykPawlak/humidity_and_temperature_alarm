#ifndef REQUEST_SUCCESS_HTML_H
#define REQUEST_SUCCESS_HTML_H

const char request_success_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8" />

    <title>Humidity and temperature alarm</title>

    <meta
        name="author"
        content="Patryk Pawlak | patrykpawlak.pl@gmail.com"
    />
    <meta
        name="viewport"
        content="width=device-width, initial-scale=1.0"
    />

    <style>
        body {
            font-family: Segoe UI, Lato, Helvetica, Roboto, Droid Sans, Ubuntu,
                Noto Sans, sans-serif;
            margin: 0;
            background: #424242;
            color: #000;
            filter: invert(100);
        }

        main {
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
            width: 100vw;
            height: 100vh;
        }

        p:first-of-type {
            margin-bottom: 20px;
        }
    </style>
</head>

<body>
    <main>
        <p>HTTP GET request was sent successfully to your ESP.</p>
        <a href="/">Return to Home Page</a>
    </main>
</body>

</html>
)rawliteral";

#endif
