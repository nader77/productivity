$(document).ready(function() {

  // Init default values.
  var maxDigits = 4;
  var digitsCounter = 0;

  /**
   * Demo click handler for the "digit" button.
   */
  var digitClickHandler = function() {
    var self = this;

    // Increment digit counter.
    digitsCounter++;

    // Enable reset button
    $('.digit.-reset').prop('disabled', false);

    $(self).toggleClass('-active');

    setTimeout( function(){
      // Remove class.
      $(self).toggleClass('-active');

      //// Return early.
      if (digitsCounter != maxDigits) {
        return;
      }
      // Disable all digits it it's the 4th digit that was clicked.
      // Strip class "active" from the breakpoints icons.
      $(".numbers-pad .digit").each(function() {
        $(this).prop('disabled', true);
      });

    } , 150 );
  };

  /**
   * On "click" handler for the "digit button".
   */
  $(".numbers-pad .digit").on("click", digitClickHandler);
});
