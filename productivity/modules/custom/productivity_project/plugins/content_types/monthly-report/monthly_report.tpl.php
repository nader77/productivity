<div class="col-sm-12">
  <div class="main-box clearfix project-box emerald-box">
    <div class="main-box-body clearfix">
      <h1>Monthly Report<small> - <?php print $project_title; ?></small></h1>
      <?php $total_tables_amount = 0; ?>
      <?php foreach($tables as $index => $table): ?>
        <h2><?php print strtoupper($table_titles[$index]); ?></h2>
        <?php print $table; ?>
          <span class="pull-right">Total: <?php print $total_per_types[$table_titles[$index]] . ' ' . $total_currency_per_types[$table_titles[$index]]; ?></span>
          <?php $total_tables_amount += $total_per_types[$table_titles[$index]] ?>
      <?php endforeach; ?>
      <div class="col-sm-offset-9 col-sm-3">TOTAL: <?php print $total_tables_amount . ' ' . $total_currency_per_types[$table_titles[$index]]; ?></div>
    </div>
  </div>
</div>
