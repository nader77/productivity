window.onload = function() {
  var result = Viz(dataSVG);
  document.body.innerHTML += result;

  //var image = Viz(dataSVG, { format: "png-image-element" });
  //document.body.appendChild(image);
}