$(document).ready(function() {

  // Init default values.
  var maxDigits = 4;
  var digitsCounter = 0;
  var validPinCode = '1234';
  var projectSelected = false;

  // Elements
  var $deleteButton = $('button.-delete');
  var $codePin = $('.code .pin');
  var $dynamicIcon = $('.-dynamic-icon');

  // Dummy ping to server to check connectivity.
  CheckServerConnection(1700);

  // Dummy "digit" button click.
  var digitClickHandler = function() {
    var self = this;

    // Delete dynamic icon.
    $dynamicIcon.html('');

    // Add class "-active" for UX.
    toggleButtonActivity(self);

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

    // Delete dynamic icon.
    $dynamicIcon.html('');

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
  };

  // Dummy server response.
  function serverResponse() {

    // Displaying the loader.
    $dynamicIcon.append('<i class="fa fa-circle-o-notch fa-spin"></i>');

    // Disable all buttons - while request is still in progress.
    DisableAllButtons();

    setTimeout(function(){
      // Delete icon.
      $dynamicIcon.html('');
      // Interpolate server response.
      $('.code .pin').text() === validPinCode ? responseSuccess() : responseError();

    }, 500)
  };

  // Toggle button activity
  function toggleButtonActivity(button) {
    // Add active class
    $(button).addClass('-active');

    setTimeout( function(){
      // Remove class.
      $(button).removeClass('-active');
    }, 45);
  };

  // Turn "ON" the led "light" indicator.
  function CheckServerConnection(time) {
    setInterval( function(){
      // Remove class.
      $('.led .light').toggleClass('on');
    }, time);
  };

  // Server returns "success" response.
  function responseSuccess() {
    $dynamicIcon.append('<i class="fa fa-check -success"></i>');
    DisableAllButtons();

    setTimeout(function(){
      // Reset the dashboard.
      reset();
      // Delete dynamic icon.
      $dynamicIcon.html('');
    }, 2000)

  };

  // Server returns "error" response.
  function responseError() {
    $dynamicIcon.append('<i class="fa fa-exclamation-triangle -error"></i>');
    reset();
  };

  // Disable all buttons.
  function DisableAllButtons() {
    // Disable all buttons - while request is still in progress.
    $('button').each(function() {
      $(this).prop('disabled', true);
    });
  };

  // Enable all buttons.
  function EnableAllButtons() {
    // Disable all buttons - while request is still in progress.
    $('button').each(function() {
      $(this).prop('disabled', false);
    });
  };

  // Delete "pin-code".
  function DeletePinCode() {
    $('.code .pin').text('');
    digitsCounter = 0;
  };

  // Reset the dashboard.
  function reset() {
    DeletePinCode();
    EnableAllButtons();
    $deleteButton.prop('disabled', true);
  }

  // "Digit" button click handler callback.
  $(".numbers-pad .digit").on("click", digitClickHandler);

  // "Project" button click handler callback.
  $(".projects button.item").on("click", function() {
    $(this).toggleClass('-active');
    projectSelected = !projectSelected;
    console.log(projectSelected);
  });

  // Delete button click handler callback.
  $deleteButton.on("click", deleteButtonHandler);

});
