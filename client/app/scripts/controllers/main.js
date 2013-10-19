'use strict';

angular.module('easyAdminApp')
  .controller('MainCtrl', function ($scope) {


     var colors = {
        darkGreen: "#779148",
        red: "#C75D5D",
        green: "#96c877",
        blue: "#6e97aa",
        orange: "#ff9f01",
        gray: "#6B787F",
        lightBlue: "#D4E5DE"
      };


    // TODO: convert into directive.
    $(".sparkline").each(function() {
      var barSpacing, barWidth, color, height;
      color = $(this).attr("data-color") || "red";
      height = "18px";
      if ($(this).hasClass("big")) {
        barWidth = "5px";
        barSpacing = "2px";
        height = "30px";
      }
      return $(this).sparkline("html", {
        type: "bar",
        barColor: colors[color],
        height: height,
        barWidth: barWidth,
        barSpacing: barSpacing,
        zeroAxis: false
      });
    });

    $scope.awesomeThings = [
      'HTML5 Boilerplate',
      'AngularJS',
      'Karma'
    ];
  });
