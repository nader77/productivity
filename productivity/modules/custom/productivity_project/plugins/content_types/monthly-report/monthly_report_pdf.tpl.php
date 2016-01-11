<html>
<head>
  <style>
    @page {
      margin: 25px;
    }
    body {
      font-family: "Open Sans", sans-serif;
    }
    .gizra-logo {
      display: inline;
      font-family: Abril Fatface;
      font-size: 3.5em;
      color: #e27058;
      float: right;
    }
    h2 {
      display: inline;
    }
    h3.table-header {
      margin-top: 1%;
    }
    table {
      width: 100%;
    }
    table.table-hover
    td:nth-child(1),
    td:nth-child(3),
    td:nth-child(4),
    td:nth-child(5) {
      width: 15%;
    }
    td:nth-child(2) {
      width: 40%;
    }
    .table-striped > tbody > tr:nth-child(odd) > td, .table-striped > tbody > tr:nth-child(odd) > th {
      background-color: #f9f9f9;
    }
    .table tbody > tr > td {
      vertical-align: middle;
      border-top: 1px solid #e7ebee;
      padding: 12px 8px;
    }
    .col-sm-12 {
      padding: 0 8px;
      width: 100%;
      position: relative;
      min-height: 1px;
    }
    .pull-right {
      display: inline;
      float: right;
    }
  </style>
</head>
<body lang=EN-US>
<div class="section">
  <h2>Monthly Report<small> - <?php print $project_title; ?></small></h2>
  <h1 class="gizra-logo">gizra</h1>

  <!-- BEGIN Tables -->
  <?php $total_tables_amount = 0; ?>
  <?php foreach($tables as $index => $table): ?>
    <h3 class="table-header"><?php print strtoupper($table_titles[$index]); ?></h3>
    <?php print $table; ?>
    <div class="col-sm-12">
      <span class="pull-right">Total: <?php print $total_per_types[$table_titles[$index]] . ' ' . $total_currency_per_types[$table_titles[$index]]; ?></span>
    </div>
    <?php $total_tables_amount += $total_per_types[$table_titles[$index]] ?>
  <?php endforeach; ?>
  <div class="col-sm-12">
    <span class="pull-right">TOTAL: <?php print $total_tables_amount . ' ' . $total_currency_per_types[$table_titles[$index]]; ?></span>
  </div>
  <!-- END Tables -->

  </p>
</div>
</body>
</html>