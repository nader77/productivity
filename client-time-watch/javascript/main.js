$(document).ready(function() {

  function is_touch_device() {
    return 'ontouchstart' in window || 'onmsgesturechange' in window;
  }

  // Init default values.
  var maxDigits = 4;
  var digitsCounter = 0;
  var validPinCode = '1234';
  var projectSelected = false;
  var startDeviceClick = is_touch_device() ? 'touchstart' : 'mousedown';
  var endDeviceClick = is_touch_device() ? 'touchend' : 'mouseup';

  // Elements
  var $deleteButton = $('button.-delete');
  var $codePin = $('.code .pin');
  var $dynamicIcon = $('.-dynamic-icon');
  var $viewWrapper = $('.view .main');

  // Dummy ping to server to check connectivity.
  CheckServerConnection(1700);

  // Dummy "digit" button click.
  var digitClickHandler = function() {
    var self = this;

    // Delete dynamic icon.
    $dynamicIcon.html('');

    // Add class "-active" for UX.
    //$(self).addClass('-active');
    $(self).toggleClass('-active');

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
    //$(self).addClass('-active');
    $(self).toggleClass('-active');

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

      // Display the view.
      $viewWrapper.addClass('-active')
    }, 500)
  }

  // Turn "ON" the led "light" indicator.
  function CheckServerConnection(time) {
    setInterval( function(){
      // Remove class.
      $('.led .light').toggleClass('on');
    }, time);
  }

  // Server returns "success" response.
  function responseSuccess() {
    $dynamicIcon.append('<i class="fa fa-check -success -in"></i>');
    DisableAllButtons();

    setTimeout(function(){
      // Reset the dashboard.
      reset();
      // Delete dynamic icon.
      $dynamicIcon.html('');

      // Hide the view.
      $viewWrapper.removeClass('-active')
    }, 2500)
  }

  // Server returns "error" response.
  function responseError() {
    $dynamicIcon.append('<i class="fa fa-exclamation-triangle -error"></i>');
    reset();
  }

  // Disable all buttons.
  function DisableAllButtons() {
    // Disable all buttons - while request is still in progress.
    $('button').each(function() {
      $(this).prop('disabled', true);
    });
  }

  // Enable all buttons.
  function EnableAllButtons() {
    // Disable all buttons - while request is still in progress.
    $('button').each(function() {
      $(this).prop('disabled', false);
    });
  }

  // Delete "pin-code".
  function DeletePinCode() {
    $('.code .pin').text('');
    digitsCounter = 0;
  }

  // Reset the dashboard.
  function reset() {
    DeletePinCode();
    EnableAllButtons();
    $deleteButton.prop('disabled', true);
  }

  // "Project" button click handler callback.
  $('button.project').on(startDeviceClick, function() {
    $(this).toggleClass('-active');
    projectSelected = !projectSelected;
  });

  // "Digit" button click handler callback.
  $('.numbers-pad .digit').on(startDeviceClick, digitClickHandler);
  $('.numbers-pad .digit').on(endDeviceClick, function() {
    // Toggle active class
    //$(this).removeClass('-active');
    $(this).toggleClass('-active');
  });


  // Delete button click handler callback.
  $deleteButton.on(startDeviceClick, deleteButtonHandler);
  $deleteButton.on(endDeviceClick, function(){
    // Toggle active class
    //$(this).removeClass('-active');
    $(this).toggleClass('-active');
  });

});
