$(document).ready(function() {

  // Init default values.
  var maxDigits = 4;
  var digitsCounter = 0;
  var $deleteButton = $('button#delete');
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

    // Display the target "digit" value.
    $($('.code .pin').get(digitsCounter)).text($(self).text());

    // Increment digit counter.
    digitsCounter++;

    // Enable reset button
    $deleteButton.prop('disabled', false);

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
  var deleteButtonkHandler = function() {
    var self = this;

    // On click add class active.
    $(self).addClass('-active');

    setTimeout( function(){
      // Remove class.
      $(self).removeClass('-active');
    }, 45);

    // Delete last digit from the record.
    $($('.code .pin').get(digitsCounter - 1)).text('');
    digitsCounter--;
  }

  // button click handler callback.
  $(".numbers-pad .digit").on("click", digitClickHandler);

  // Project button click handler callback.
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



});
