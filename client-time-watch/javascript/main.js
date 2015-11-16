$(document).ready(function() {

  // Init default values.
  var maxDigits = 4;
  var digitsCounter = 0;
  var $resetButton = $('button.-reset');
  var pinCode = '';
  var validPinCode = '1234';

  // Mockup the connection led light indicator.
  setInterval( function(){
    // Remove class.
    $('.led .light').toggleClass('on');
  }, 1700);

  // Demo click handler for the "digit" button.
  var digitClickHandler = function() {
    var self = this;

    var digitValue = $(self).text();
    $($('.code .pin').get(digitsCounter)).text(digitValue);
    pinCode += digitValue;

    // Increment digit counter.
    digitsCounter++;

    // Enable reset button
    $resetButton.prop('disabled', false);

    // Add active class
    $(self).addClass('-active');

    setTimeout( function(){
      // Remove class.
      $(self).removeClass('-active');

      // Return early.
      if (digitsCounter != maxDigits) {
        return;
      }
      serverResponse();
    }, 45);
  };

  // Demo click handler for the "reset" button.
  var resetClickHandler = function() {
    var self = this;

    $(self).addClass('-active');

    $($('.code .pin').get(digitsCounter - 1)).text('');
    digitsCounter--;

    setTimeout( function(){
      // Remove class.
      $(self).removeClass('-active');
    }, 45);
  }

  // Digit click handler callback.
  $(".numbers-pad .digit").on("click", digitClickHandler);

  // Digit click handler callback.
  $(".projects button.item").on("click", function() {
    $(this).toggleClass('-active');
  });

  // Mockup for the server response
  function serverResponse() {
    var $icon = $('.icon.dynamic');
    $icon.append('<i class="fa fa-circle-o-notch fa-spin"></i>');

    setTimeout(function(){
      // Clear inner content first.
      $icon.html('');

      // Enable all digits buttons.
      $('button').each(function() {
        $(this).prop('disabled', false);
      });

      // In case of success.
      if (pinCode === validPinCode) {
        $icon.append('<i class="fa fa-check -success"></i>');
      }
      // In case of error.
      else {
        $icon.append('<i class="fa fa-times -error"></i>');
      }
    }, 300)

    // Disable all digits buttons it it's the 4th digit that was clicked.
    $('button').each(function() {
      $(this).prop('disabled', true);
    });
  }

  // Reset button click handler callback.
  $resetButton.on("click", resetClickHandler);

});
