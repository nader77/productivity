<div class="col-sm-12">
  <div class="main-box clearfix project-box emerald-box">
    <div class="main-box-body clearfix">
      <h1>Monthly Report<small> - <?php print $project_title; ?></small></h1>

      <!-- BEGIN Search Filter -->
      <div class="col-sm-12">
        <div class="col-sm-5"><p>Project: </p></div>
        <div class="col-sm-3"><p>Date: </p></div>
      </div>
      <div class="col-sm-12">
        <div class="col-sm-5 ">
          <select class="form-control">
            <option>1</option>
            <option>2</option>
          </select>
        </div>
        <div class="col-sm-3">
          <input type="month" class="form-control" placeholder="Blah">
        </div>
        <input class="btn btn-primary col-sm-1" type="submit" value="Apply">
      </div>
      <!-- END Search Filter -->

      <!-- BEGIN Tables -->
      <?php $total_tables_amount = 0; ?>
      <?php foreach($tables as $index => $table): ?>
        <h2><?php print strtoupper($table_titles[$index]); ?></h2>
        <?php print $table; ?>
          <span class="pull-right">Total: <?php print $total_per_types[$table_titles[$index]] . ' ' . $total_currency_per_types[$table_titles[$index]]; ?></span>
          <?php $total_tables_amount += $total_per_types[$table_titles[$index]] ?>
      <?php endforeach; ?>
      <div class="col-sm-offset-9 col-sm-3">TOTAL: <?php print $total_tables_amount . ' ' . $total_currency_per_types[$table_titles[$index]]; ?></div>
      <!-- END Tables -->
    </div>
  </div>
</div>
