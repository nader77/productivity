window.onload = function() {
  var result = Viz(dataSVG, { format: "png-image-element" });
  document.body.appendChild(result);
  //document.body.innerHTML += result;
}