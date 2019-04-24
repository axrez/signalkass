const express = require('express');

const router = express.Router();

const Measure = require('../../models/Measurement');
const MeasureMap = require('../../models/MeasurementMap');

// @route:  api/device/post
// @disc:   Let the osciloscope update the database
// @access: Should be private but public for know
router.post('/post', (req, res) => {
  const array = JSON.parse(`[${req.body.data}]`);
  console.log(array.constructor === Array);

  const date = new Date();

  const newMeasure = new Measure({
    data: req.body.data,
    created: date,
  });

  const newMeasureMap = new MeasureMap({
    created: date,
  });

  newMeasure
    .save()
    .then(mes =>
      newMeasureMap
        .save()
        .then(() => res.json(mes))
        .catch(err => console.log(err))
    )
    .catch(err => console.log(err));
});

module.exports = router;
