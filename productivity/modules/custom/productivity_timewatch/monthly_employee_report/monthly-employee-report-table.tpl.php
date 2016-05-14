<h3><?php print t('@year - @month - @username', array('@year' => $year, '@month' => $month, '@username' => $username)); ?></h3>
<?php print $table; ?>
<div class="row">
  <h3>Summary</h3>
  <div class="col-sm-12">
    <?php print $table_summary; ?>
  </div>
</div>
<h3>Signature</h3>
<div class="row">
  <div class="col-sm-6">
    Brice Lenfant (MOP manager):
  </div>
  <div class="col-sm-6">
    <?php print $username; ?>:
  </div>
</div>