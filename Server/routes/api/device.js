const express = require('express');
const router = express.Router();

const Measure = require('../../models/Measurement');

// @route:  api/device/post
// @disc:   Let the osciloscope update the database
// @access: Should be private but public for know
router.post("/post", (req, res) => {
  array = JSON.parse( "[" + req.body.data + "]");
  console.log(array.constructor === Array);
  
  const newMeasure = new Measure({
    data: req.body.data,
    created: new Date,
  });

  newMeasure.save()
    .then(mes => res.json(mes))
    .catch(err => console.log(err));

});

module.exports = router;

