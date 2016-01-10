'use strict';

(function ($) {
  Drupal.behaviors.monthlyReports = {
    attach: function (context, settings) {
      // get the current month and year.
      var date = new Date();
      var input_date = date.getFullYear() + '-' + date.getMonth() + 1;
      // Set the month and year in the input month
      $('input[type=month]').val(input_date);

      console.log(settings);
    }
  };

})(jQuery);

