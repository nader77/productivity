<div class="col-sm-12">
  <div class="main-box clearfix project-box emerald-box">
    <div class="main-box-body clearfix">
      <h1>Monthly Report<small> - <?php print $project_title; ?></small></h1>

      <div id="search-filter" class="row">
        <div class="col-sm-12 ">
          <div class="col-sm-5"><p>Project: </p></div>
          <div class="col-sm-3"><p>Date: </p></div>
        </div>
        <div class="col-sm-12">
          <div class="col-sm-5 ">
            <select id="project_filter" class="form-control">
              <?php foreach($projects as $project): ?>
                <option value="<?php print $project[1];?>"<?php print ($project[1] === $current_project_id) ? 'selected' : ''; ?>><?php print $project[0]; ?></option>
              <?php endforeach; ?>
            </select>
          </div>
          <div class="col-sm-3">
            <input id="date_filter" type="month" class="form-control" />
          </div>
          <input class="btn btn-primary col-sm-1" type="submit" value="Apply" />
        </div>
      </div>

      <!-- BEGIN Tables -->
      <?php $total_tables_amount = 0; ?>
      <?php foreach($tables as $index => $table): ?>
        <h2 class="table-header"><?php print strtoupper($table_titles[$index]); ?></h2>
        <?php print $table; ?>
        <div class="col-sm-12">
          <span class="col-sm-2 pull-right">Total: <?php print $total_per_types[$table_titles[$index]] . ' ' . $total_currency_per_types[$table_titles[$index]]; ?></span>
        </div>
        <?php $total_tables_amount += $total_per_types[$table_titles[$index]] ?>
      <?php endforeach; ?>
      <div class="col-sm-12 well">
        <button type="button" class="btn btn-default">Download PDF</button>
        <span class="col-sm-2 pull-right">TOTAL: <?php print $total_tables_amount . ' ' . $total_currency_per_types[$table_titles[$index]]; ?></span>
      </div>
      <!-- END Tables -->
    </div>
  </div>
</div>

