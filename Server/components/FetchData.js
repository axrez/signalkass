import React, { useEffect, useState } from 'react';
import styled from 'styled-components';
import axios from 'axios';

import Graph from './Graph';
import DataTabel from './DataTabel';

const GraphWrapper = styled.div`
  max-width: 80vw;
  height: 30vh;
`;

const MapURI = '/api/client/map';
const GraphURI = '/api/client';
const SpeceficURI = '/api/client/specefic';

const FetchData = () => {
  const [date, setDate] = useState([]);
  const [graph, setGraph] = useState([]);
  useEffect(() => {
    // fetch the data table
    const fetchnMap = async () => {
      const { data: body } = await axios.get(MapURI);
      // Map it to an array of dates
      const tempDate = body.map(e => e.created);
      setDate(tempDate);
    };

    const fetchGraph = async () => {
      const { data } = await axios.get(GraphURI);
      setGraph(data);
    };

    fetchnMap().catch(err => console.log(err));
    fetchGraph().catch(err => console.log(err));
  }, []);

  const fetchNew = async e => {
    const dateNow = e.target.id;
    const { data } = await axios.post(SpeceficURI, { created: dateNow });
    const newGraph = data;
    setGraph(newGraph);
  };

  return (
    <>
      <GraphWrapper>
        <Graph data={graph} />
      </GraphWrapper>
      <DataTabel data={date} click={fetchNew} />
    </>
  );
};
export default FetchData;
