'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:CompaniesCtrl
 * @description
 * # CompaniesCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('TrackingCtrl', function ($scope, tracking, $stateParams, $log) {

    // Initialize values.
    $scope.tracking = tracking;
    $scope.selectedTrack = null;
    $scope.year = $stateParams.year;
    $scope.month = $stateParams.month;
    $scope.eventSources = [];

    var width = 1024;
    var startDay = 1;
    var endDay = 30;
    var getColor = d3.scale.category20c();
    var scaleLinear = d3.scale.linear().range([0, width]);

    var xAxis = d3.svg.axis().scale(scaleLinear).orient("top");
    var svg = d3.select('.tracking-data');

    scaleLinear.domain([startDay, endDay]);
    var xScale = d3.scale.linear()
      .domain([startDay, endDay])
      .range([0, width]);

    // Set header (month days).
    svg.append("g")
      .attr("class", "x axis")
      .attr("transform", "translate(0," + 0 + ")")
      .call(xAxis);

    // Prepare data by employee.
    var employee = prepareEmployeeJson(tracking);

    var j = 0;
    angular.forEach(employee, function(data, employeeName) {
      var g = svg.append("g").attr("class","journal");

      // Add the circle size.
      var circles = g.selectAll("circle")
        .data(data)
        .enter()
        .append("circle");

      var text = g.selectAll("text")
        .data(data)
        .enter()
        .append("text");

      var div = g.selectAll("button")
        .data(data)
        .enter()
        .append("text")
        .on("mouseover", mouseover1)
        .on("mouseout", mouseout);

      // Set size of circle max and min 2-9.
      var rScale = d3.scale.linear()
        .domain([0, d3.max(data, function(d) {
          return d[1];
        })])
        .range([2, 9]);

      // Add the circle using the value of hours as Radius.
      circles
        .attr("cx", function(d) {
          return xScale(d[0]);
        })
        .attr("cy", j*20+20)
        .attr("r", function(d) {
          return rScale(d[1]);
        })
        .attr("class",function(d) {
          return d[3];
        })
        .attr("data-toggle","tooltip")
        .attr("data-placement","top")
        .attr("title",function(d) {
          return d[2];
        });
//        .style("fill", function(d) {
//          return getColorByType(j, d);
//        });

      div
        .attr("y", j*20+25)
        .attr("x",function(d) { return xScale(d[0])-5; })
        .attr("data-toggle","tooltip")
        .attr("data-placement","top")
        .style("display","none")
        .text(function(d){ return d[2]; })
        .attr("title",function(d) {
          return d[2];
        });

      // Add number of hours string
      text
        .attr("y", j*20+25)
        .attr("x",function(d) { return xScale(d[0])-5; })
        .attr("class","value")
        .text(function(d){ return d[1]; })
        .style("fill", function() { return getColor(j); })
        .style("display","none");

      // Trying to add
//      text
//        .attr("y", j*20+25)
//        .attr("x",function(d) { return xScale(d[0])-5; })
//        .attr("class","project")
//        .text(function(d){ return d[2]; })
//        .style("fill", function() { return getColor(j); })
//        .style("display","none");

      // Add name of employee
      g.append("text")
        .attr("y", j*20+25)
        .attr("x",width+20)
        .attr("class","label")
        .text(employeeName)
        .style("fill", function() { return getColor(j); })
        .on("mouseover", mouseover)
        .on("mouseout", mouseout);

      // Interator.
      j++;
    });

    function getColorByType(j, d) {
      return getColor(j);
    }

    function mouseover(p) {
      var g = d3.select(this).node().parentNode;
      d3.select(g).selectAll("circle").style("display","none");
      d3.select(g).selectAll("text.value").style("display","block");
    }

    function mouseover1(p) {
      var g = d3.select(this).node().parentNode;
      d3.select(g).select("text").style("display","none");
      d3.select(g).select("text.value").style("display","block");
    }

    function mouseout(p) {
      var g = d3.select(this).node().parentNode;
      d3.select(g).selectAll("circle").style("display","block");
      d3.select(g).selectAll("text.value").style("display","none");
    }

    /**
     * Prepare the json for display.
     * @param tracking
     * @returns Employee json
     */
    function prepareEmployeeJson(tracking) {
      var employee = {};
      angular.forEach(tracking, function(value) {
        if (value.employee == undefined) {
          if (value.type == 'regular') {
            // If no employee use project name.
            value.employee = value.projectName;
          }
          value.employee = value.type;
        }
        if (employee[value.employee] == undefined) {
          employee[value.employee] = [];
        }
        // Convert days to hours.
        if (value.length.period == 'day') {
          value.length.interval = parseInt(value.length.interval) * 8;
        }
        // If no project time, print special day type instead.
        if (value.type != 'regular') {
          value.projectName = value.type;
          value.length.interval = 8;
        }

        if (employee[value.employee] == undefined) {
          employee[value.employee] = [];
        }
        employee[value.employee].push([value.day, value.length.interval, value.projectName, value.type]);
      });
      return employee;
    }

    $(function () {
      $('[data-toggle="tooltip"]').tooltip()
    })

    /**
     * Set the selected Company.
     *
     * @param int id
     *   The company ID.
     */
    var setSelectedCompany = function(id) {
      $scope.selectedTrack = null;

      angular.forEach($scope.tracking, function(value) {
        if (value.id == id) {
          $scope.selectedTrack = value;
        }
      });
    };

    if ($stateParams.trackId) {
      setSelectedCompany($stateParams.trackId);
    }
  });
