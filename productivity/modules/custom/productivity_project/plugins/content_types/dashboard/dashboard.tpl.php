<?php print $header; ?>
<div class="row">
  <?php foreach($rendered_nodes as $node):?>
    <div class="col-lg-4 col-md-6 col-sm-6">
      <?php print $node; ?>
    </div>
  <?php endforeach; ?>
</div>

