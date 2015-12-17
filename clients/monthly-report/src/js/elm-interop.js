var elmApp = Elm.fullscreen(Elm.Main, {host: ""});

// Extract the backend URL from the current URL. Assuming the app is one folder
// above the backend.
// Remove the last folder from the current URL; I.e. convert
// http://localhost/productivity/www/monthly-report/ to
// http://localhost/productivity/www
var urlParts = window.location.href.split("/");
urlParts.pop();
urlParts.pop();
backendUrl = urlParts.join("/");
elmApp.ports.host.send(backendUrl);
