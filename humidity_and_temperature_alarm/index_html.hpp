#ifndef INDEX_HTML_H
#define INDEX_HTML_H

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8" />

    <title>Humidity and temperature alarm</title>

    <meta name="author" content="Patryk Pawlak | patrykpawlak.pl@gmail.com" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />

    <script defer>
       setInterval(function () {
         let xhttp = new XMLHttpRequest();
         xhttp.onreadystatechange = function () {
           if (this.readyState == 4 && this.status == 200) {
             document.getElementById("humidity").innerHTML = this.responseText;
           }
         };
         xhttp.open("GET", "/humidity", true);
         xhttp.send();
       }, 2000);

       setInterval(function () {
         let xhttp = new XMLHttpRequest();
         xhttp.onreadystatechange = function () {
           if (this.readyState == 4 && this.status == 200) {
             document.getElementById("temperature").innerHTML = this.responseText;
           }
         };
         xhttp.open("GET", "/temperature", true);
         xhttp.send();
       }, 2000);
    </script>

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

      .container {
        display: grid;
        grid-gap: 40px;
        align-items: end;
      }

      .rgb-color-output-container {
        height: 40px;
        margin-bottom: 10px;
        filter: invert(100);
      }

      #rgb-color-output
      {
        height: 100%;
      }

      form
      {
          margin-block-end: 0;
      }

      .rgb-container > form
      {
          display: grid;
          grid-template-columns: repeat(3, 2fr) 1fr;
          grid-gap: 30px;
      }

      input[type="number"]
      {
          width: 70px;
      }

      input[type="submit"]
      {
          width: 6em;
          height: 2em;
      }
    </style>
  </head>
  <body>
    <main>
      <h1>Humidity and temperature alarm</h1>
      <div class="container">
        <div class="rgb-container">
          <h2>Alarm RGB LED color</h2>
          <div class="rgb-color-output-container">
            <div id="rgb-color-output" >Loading color...</div>
          </div>
          <form action="/set">
            <span>
              <label for="range-red">Red: </label>
              <input
                id="range-red"
                name="red"
                type="range"
                min="0"
                max="255"
                step="1"
                required
              />
            </span>
            <span>
              <label for="range-green">Green: </label>
              <input
                id="range-green"
                name="green"
                type="range"
                min="0"
                max="255"
                step="1"
                required
              />
            </span>
            <span>
              <label for="range-blue">Blue: </label>
              <input
                id="range-blue"
                name="blue"
                type="range"
                min="0"
                max="255"
                step="1"
                required
              />
            </span>
            <input type="submit" value="Submit" />
          </form>
        </div>
        <div class="humidity-container">
          <h2>Humidity</h2>
          <p>Humidity: <span id="humidity">Loading...</span>&#37;</p>
          <p>Humidity threshold: <span id="humidity-threshold">Loading...</span>&#37;</p>

          <form action="/set">
            <label for="humidity-threshold-input">Enter humidity threshold: </label>
            <input
              id="humidity-threshold-input"
              name="humidity"
              type="number"
              min="0"
              max="100"
              step="0.1"
              placeholder="0.0"
              required
            />
            <input type="submit" value="Submit" />
          </form>
        </div>
        <div class="temperature-container">
          <h2>Temperature</h2>
          <p>Temperature: <span id="temperature">Loading...</span>&#8451;</p>
          <p>Temperature threshold: <span id="temperature-threshold">Loading...</span>&#8451;</p>

          <form action="/set">
            <label for="temperature-threshold-input">Enter temperature threshold: </label>
            <input
              id="temperature-threshold-input"
              name="temperature"
              type="number"
              min="0"
              max="100"
              step="0.1"
              placeholder="0.0"
              required
            />
            <input type="submit" value="Submit" />
          </form>
        </div>
      </div>
    </main>
    <script defer>
      function changeColor() {
        let red_val = document.getElementById("range-red").value;
        let green_val = document.getElementById("range-green").value;
        let blue_val = document.getElementById("range-blue").value;
        let colorOutput = document.getElementById("rgb-color-output");
        let color = "rgb(" + red_val + ", " + green_val + ", " + blue_val + ")";
        colorOutput.style.backgroundColor = color;
      }

      function setColor() {
        let colorOutput = document.getElementById("rgb-color-output");
        
        let xhttp = new XMLHttpRequest();
         xhttp.onreadystatechange = function () {
           if (this.readyState == 4 && this.status == 200) {
             let arr = this.responseText.split(",");
             document.getElementById("range-red").value = parseInt(arr[0].split("(")[1]);
             document.getElementById("range-green").value = parseInt(arr[1].trim());
             document.getElementById("range-blue").value = parseInt(arr[2].split(")")[0].trim());
             console.log(this.responseText);
             colorOutput.style.backgroundColor = this.responseText;
             colorOutput.innerHTML = "";
           }
         };
         xhttp.open("GET", "/rgb-color", true);
         xhttp.send();
      }

      function setHumidityThreshold() {        
        let xhttp = new XMLHttpRequest();
         xhttp.onreadystatechange = function () {
           if (this.readyState == 4 && this.status == 200) {
             document.getElementById("humidity-threshold").innerHTML = this.responseText;

             document.getElementById("humidity-threshold-input").placeholder = parseFloat(this.responseText);
           }
         };
         xhttp.open("GET", "/humidity-threshold", true);
         xhttp.send();
      }

      function setTemperatureThreshold() {
        let xhttp = new XMLHttpRequest();
         xhttp.onreadystatechange = function () {
           if (this.readyState == 4 && this.status == 200) {
             document.getElementById("temperature-threshold").innerHTML = this.responseText;

             document.getElementById("temperature-threshold-input").placeholder = parseFloat(this.responseText);
           }
         };
         xhttp.open("GET", "/temperature-threshold", true);
         xhttp.send();
      }

      document
        .getElementById("range-red")
        .addEventListener("input", changeColor);
      document
        .getElementById("range-green")
        .addEventListener("input", changeColor);
      document
        .getElementById("range-blue")
        .addEventListener("input", changeColor);

        document.addEventListener('DOMContentLoaded', changeColor);
        document.addEventListener('DOMContentLoaded', setColor);
        document.addEventListener('DOMContentLoaded', setHumidityThreshold);
        document.addEventListener('DOMContentLoaded', setTemperatureThreshold);
    </script>
  </body>
</html>)rawliteral";

#endif
