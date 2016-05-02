
<form id="acceptance" class="form-horizontal form-inline">
  <fieldset>
    <span>Date of handover:</span>
    <input type="text" id="month" name="month" class="monthPicker form-control" />
    <table class="table table-bordered table-striped table-hover table-condensed table-responsive">
      <thead>
      <tr>
        <th>Types</th>
        <th>Status</th>
        <th>Name of person approving</th>
      </tr>
      </thead>
      <tbody>
        <?php print $rows; ?>
      </tbody>
    </table>
    <span id="submit_result"></span>
  </fieldset>
</form>

<script>
  // Date picker.
  jQuery('input[name=month]').datepicker( {
    format: "MM dd, yyyy",
    minViewMode: 0,
    autoclose: true,
    startView: 0,
    todayBtn: "linked",
    keyboardNavigation: false,
    forceParse: false
  } );
  console.log(Drupal.settings);
  jQuery('input[name=month]').datepicker('setDate', Drupal.settings.utcDate);
  // Autosave.
  jQuery("#acceptance select, input[name=month]").change(function() {
    var data = {'data':{}, 'date':{}};
    // Gather all data from table.
    jQuery("#acceptance select").each(function() {
      data['data'][jQuery(this).attr('id')] = jQuery(this).val();
    });
    // Get date.
    data['date'] = jQuery('input[name=month]').datepicker('getDate');
    console.log(data);
    jQuery('#submit_result').text('Saving...').show();
    jQuery.ajax({
      type: "POST",
      url: Drupal.settings.submitAcceptanceURL,
      data: data
      })
      .done(function() {
        jQuery('#submit_result').text('Saving...').fadeOut();
      })
      .fail(function() {
        jQuery('#submit_result').text('failed to Saved').fadeOut();
      });
  });
</script>