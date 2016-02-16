'use strict';

(function ($) {

  /**
   * Create new URL from project id and date.
   *
   * @param base_url
   *  The base URL of the page.
   *
   * @returns {string}
   *  New URL string.
   */
  function create_new_url(base_url) {
    var project_id = $('#project_filter').val();
    var date = $('#date_filter').val().split('-');

    return base_url + "/monthly-report/" + project_id + "/" + date[0] + "/" + date[1];
  }

  /**
   * Set the current year and month on date input.
   */
  function set_date_input() {
    // get the current month and year.
    var date = new Date();
    var input_date = date.getFullYear() + '-' + date.getMonth() + 1;
    // Set the month and year in the input month
    $('input[type=month]').val(input_date);
  }

  Drupal.behaviors.monthlyReports = {
    attach: function (context, settings) {
      var url = '';
      set_date_input();
      $('#project_filter').select2();

      // Project select and date input handler.
      $('#project_filter, #date_filter').change(function() {
        url = create_new_url(settings['monthly_report']['base_url']);
      }).change();

      // Apply filter button handler.
      $('.btn-primary[type=submit]').click(function() {
        window.location.href = url;
      });
    }
  };
})(jQuery);

