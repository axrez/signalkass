import React, { useEffect, useState } from 'react';
import styled from 'styled-components';
import axios from 'axios';

import Graph from './Graph';
import DataTabel from './DataTabel';

const GraphWrapper = styled.div`
  max-width: 80vw;
  height: 30vh;
`;

const uri = '/api/client/map';

const FetchData = () => {
  const [date, setDate] = useState(0);
  useEffect(() => {
    // fetch the data table
    const fetchnMap = async () => {
      const { data: body } = await axios(uri);
      const tempDate = body.map(e => e.created);
      setDate(tempDate);
    };

    fetchnMap().catch(err => console.log(err));
  }, []);
  return (
    <>
      <GraphWrapper>
        <Graph />
      </GraphWrapper>
      <DataTabel data={date} />
    </>
  );
};
export default FetchData;
