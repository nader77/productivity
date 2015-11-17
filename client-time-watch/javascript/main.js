$(document).ready(function() {

  // Init default values.
  var maxDigits = 4;
  var digitsCounter = 0;
  var validPinCode = '1234';

  // Elements
  var $deleteButton = $('button.-delete');
  var $codePin = $('.code .pin');
  var $dynamicIcon = $('.-dynamic-icon');

  // Dummy ping to server to check connectivity.
  CheckServerConnection(1700);

  // Dummy "digit" button click.
  var digitClickHandler = function() {
    var self = this;

    // Add class "-active" for UX.
    toggleButtonActivity(self)

    // Enable the "delete" button.
    $deleteButton.prop('disabled', false);

    // Display the target "digit" value.
    $($codePin.get(digitsCounter)).text($(self).text());
    digitsCounter++;

    // Dummy request to server.
    if (digitsCounter == maxDigits) {
      serverResponse();
    }
  };

  // Dummy "delete" button click.
  var deleteButtonHandler = function() {
    var self = this;

    if (digitsCounter == maxDigits) {
      // Delete icon.
      $dynamicIcon.html('');
    }

    // Add class "-active" for UX.
    toggleButtonActivity(self)

    // Delete the last digit from the record.
    $($codePin.get(digitsCounter - 1)).text('');
    digitsCounter--;

    // In case we have no "digit" at all.
    if (!digitsCounter) {
      // Disable the "delete" button.
      $deleteButton.prop('disabled', true);
    }
  }


  // "Digit" button click handler callback.
  $(".numbers-pad .digit").on("click", digitClickHandler);

  // "Project" button click handler callback.
  $(".projects button.item").on("click", function() {
    $(this).toggleClass('-active');
  });

  // Delete button click handler callback.
  $deleteButton.on("click", deleteButtonHandler);

  // Dummy server response.
  function serverResponse() {

    // Displaying the loader.
    $dynamicIcon.append('<i class="fa fa-circle-o-notch fa-spin"></i>');

    setTimeout(function(){
      // Delete icon.
      $dynamicIcon.html('');

      // Reset all buttons.
      $('button').each(function() {
        $(this).prop('disabled', false);
      });

      // success.
      if ($('.code .pin').text() === validPinCode) {
        $dynamicIcon.append('<i class="fa fa-check -success"></i>');

        // Disable all buttons.
        $('button').each(function() {
          $(this).prop('disabled', true);
        });
      }
      // Error.
      else {
        $dynamicIcon.append('<i class="fa fa-exclamation-triangle -error"></i>');
      }
    }, 300)
  }

  // Toggle button activity
  function toggleButtonActivity(button) {
    // Add active class
    $(button).addClass('-active');

    setTimeout( function(){
      // Remove class.
      $(button).removeClass('-active');
    }, 45);
  }

  // Turn "ON" the led "light" indicator.
  function CheckServerConnection(time) {
    setInterval( function(){
      // Remove class.
      $('.led .light').toggleClass('on');
    }, time);
  }

});
