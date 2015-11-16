$(document).ready(function() {

  // Init default values.
  var maxDigits = 4;
  var digitsCounter = 0;

  // Mockup the connection led light indicator.
  setInterval( function(){
    // Remove class.
    $('.led .light').toggleClass('on');
  }, 400);

  // Demo click handler for the "digit" button.
  var digitClickHandler = function() {
    var self = this;

    // Increment digit counter.
    digitsCounter++;

    // Enable reset button
    $('.digit.-reset').prop('disabled', false);

    $(self).addClass('-active');

    setTimeout( function(){
      // Remove class.
      $(self).removeClass('-active');

      // Return early.
      if (digitsCounter != maxDigits) {
        return;
      }
      // Disable all digits it it's the 4th digit that was clicked.
      // Strip class "active" from the breakpoints icons.
      $('button').each(function() {
        $(this).prop('disabled', true).removeClass('-active');
      });

    }, 45);
  };

  // Demo click handler for the "digit" button.
  var ProjectClickHandler = function() {
    var self = this;
    $(self).toggleClass('-active');
  };

  // Digit click handler callback.
  $(".numbers-pad .digit").on("click", digitClickHandler);

  // Digit click handler callback.
  $(".projects button.item").on("click", ProjectClickHandler);
});
