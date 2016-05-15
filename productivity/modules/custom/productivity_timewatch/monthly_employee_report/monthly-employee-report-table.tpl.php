<div class="report-container">
  <div id="header" class="show-only-on-print">
    <span id="gizra-logo">gizra</span>
    <span id="project-title"><?php print t('Work Report for: @username - @date', array('@username' => $fullname, '@date' => $date)); ?></span>
  </div>

  <?php print $table; ?>
  <div class="row" style="page-break-before: always;">
    <h3>Summary</h3>
    <div class="col-sm-12">
      <?php print $table_summary; ?>
    </div>
  </div>
  <h3>Signatures</h3>
  <div class="row">
    <div class="col-sm-6">
      Brice Lenfant (MOP manager):
    </div>
    <div class="col-sm-6">
      <?php print $fullname; ?>:
    </div>
  </div>
</div>