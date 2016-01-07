<div class="col-lg-4 col-md-6 col-sm-6">
  <div class="main-box clearfix project-box emerald-box">
    <div class="main-box-body clearfix">
      <h1>Monthly Report - <?php print $project_title; ?></h1>
      <?php foreach($tables as $index => $table): ?>
        <h2><?php print strtoupper($table_titles[$index]); ?></h2>
        <?php print $table; ?>
      <?php endforeach; ?>
    </div>
  </div>
</div>
