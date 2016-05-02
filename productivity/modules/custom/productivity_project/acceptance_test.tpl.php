<form id="acceptance" class="form-horizontal">
  <fieldset>
    <table class="table table-bordered table-striped table-hover table-condensed table-responsive">
      <thead>
      <tr>
        <th>
          Types
        </th>
        <th>
          Status
        </th>
        <th>
          Name of person approving
        </th>
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
  jQuery("#acceptance select").change(function(event){
    var data = {};
    jQuery("#acceptance select").each(function() {
      data[jQuery(this).attr('id')] = jQuery(this).val();
    });
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