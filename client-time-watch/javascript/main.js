$(document).ready(function() {

  // Init default values.
  var maxDigits = 4;
  var digitsCounter = 0;
  var validPinCode = '1234';

  // Elements
  var $deleteButton = $('button#delete');
  var $codePin = $('.code .pin');

  // Dummy ping to server to check connectivity.
  CheckServerConnection(1700);

  // Dummy "digit" button click.
  var digitClickHandler = function() {
    var self = this;

    // Display the target "digit" value.
    $($codePin.get(digitsCounter)).text($(self).text());

    // Increment digit counter.
    digitsCounter++;
    console.log(digitsCounter);

    // Add class "-active" for UX.
    toggoleButtonActivity(self)

    // Enable the "delete" button.
    $deleteButton.prop('disabled', false);

    // Dummy request to server.
    if (digitsCounter == maxDigits) {
      serverResponse();
      return;
    }
  };

  // Demo click handler for the "reset" button.
  var deleteButtonkHandler = function() {
    var self = this;

    // Add class "-active" for UX.
    toggoleButtonActivity(self)

    // Delete the last digit from the record.
    $($codePin.get(digitsCounter - 1)).text('');
    digitsCounter--;
  }

  // "Digit" button click handler callback.
  $(".numbers-pad .digit").on("click", digitClickHandler);

  // "Project" button click handler callback.
  $(".projects button.item").on("click", function() {
    $(this).toggleClass('-active');
  });

  // Delete button click handler callback.
  $deleteButton.on("click", deleteButtonkHandler);

  // Dummy server response.
  function serverResponse() {

    // Dynamic icon.
    var $icon = $('#dynamic-icon');

    // Displaying the loader.
    $icon.append('<i class="fa fa-circle-o-notch fa-spin"></i>');

    setTimeout(function(){
      // Clear inner content first.
      $icon.html('');

      // Reset all buttons.
      $('button').each(function() {
        $(this).prop('disabled', false);
      });

      // In case of success.
      if ($('.code .pin').text() === validPinCode) {
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

  // Toggle button activity
  function toggoleButtonActivity(button) {
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
