<div class="col-sm-12">
  <div class="main-box clearfix project-box emerald-box">
    <div class="main-box-body clearfix">
      <h1>Monthly Report - <?php print $project_title; ?></h1>
      <?php foreach($tables as $index => $table): ?>
        <h2><?php print strtoupper($table_titles[$index]); ?></h2>
        <?php print $table; ?>
        <span class="pull-right">Total: <?php print $total_per_types[$table_titles[$index]]; ?></span>
      <?php endforeach; ?>
    </div>
  </div>
</div>
