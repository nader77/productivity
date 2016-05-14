'use strict';

(function ($) {


  var month = [
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
  ];

  /**
   * Create new URL from project id and date.
   *
   * @param base_url
   *  The base URL of the page.
   *
   * @returns {string}
   *  New URL string.
   */
  function create_new_url(base_url, all, year) {
    var uid = $('#uid').val();
    var val = $(".monthPicker").val();
    var res = val.split(",");

    // Full year link
    if (year) {
      if (res[1].trim() == 'all') {
        return false;
      }
      return base_url + "/monthly-employee-report/" + uid + "/" + res[1].trim() + "/all";
    }

    // All time link.
    if (all) {
      return base_url + "/monthly-employee-report/" + uid + "/all/all";
    }

    // Specific month link
    return base_url + "/monthly-employee-report/" + uid + "/" + res[1].trim() + "/" + get_month_num(res[0].trim());
  }

  /**
   * Convert num to month.
   */
  function get_month_name(month_num) {
    if (month_num == 'all') {
      return month_num;
    }
    return month[month_num - 1];
  }

  /**
   * Convert month to num.
   */
  function get_month_num(month_name) {
    var i;
    for (i = 0; i < 12; i++) {
      if (month[i] == month_name) {
        return i+1;
      }
    }
    return 'all';
  }

  /**
   * Set the current year and month on date input.
   */
  function set_date_input(settings) {
    // get the current month and year.
    var input_date = get_month_name(settings['report']['month']) + ', ' +  settings['report']['year'];
    $('.monthPicker').attr('value', input_date);
  }

  Drupal.behaviors.monthlyReports = {
    attach: function (context, settings) {
      set_date_input(settings);
      $('#uid').select2();
      $(".btn.year").popover({delay: { "show": 500, "hide": 100 }});

      // Apply filter button handler.
      $('.apply').click(function() {
        window.location.href = create_new_url(settings['report']['base_url'], false, false);
      });
      // Get all pdfs, request a file for each.
      $('.allpdf').click(function() {
        var obj = settings['report']['employees'];
        for (var prop in obj) {
          if (obj.hasOwnProperty(prop)) {
            var uid = obj[prop].uid;
            var url = settings['report']['pdf_url_start'] + '/' + uid + settings['report']['pdf_url_end'];
            window.open(url, '_blank');
          }
        }
      });

      $('input[name=month]').datepicker( {
        format: "MM, yyyy",
        minViewMode: 1,
        autoclose: true,
        startDate: "1/2015",
        startView: 1,
        todayBtn: "linked",
        keyboardNavigation: false,
        forceParse: false
      } );
    }
  };
})(jQuery);

