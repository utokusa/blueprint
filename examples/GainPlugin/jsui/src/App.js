import AnimatedFlexBoxExample from './AnimatedFlexBox';
import Label from './Label';
import Meter from './Meter';
import ParameterToggleButton from './ParameterToggleButton'
import ParameterSlider from './ParameterSlider'

import React, { Component } from 'react';

import {
  Canvas,
  Image,
  Text,
  TextInput,
  View,
  Slider,
} from 'react-juce';


function animatedDraw(ctx) {
  let now = (Date.now() / 10);
  let width = now % 100;
  let red = Math.sqrt(width / 100) * 255;
  let hex = Math.floor(red).toString(16);

  // TODO: Should update the ctx proxy to convert from javascript hex strings, aka
  // #ffffaa to juce's Colour::fromString() API which is ffffffaa.
  ctx.fillStyle = `ff${hex}ffaa`;
  ctx.fillRect(0, 0, width, 2);
}

class App extends Component {
  constructor(props) {
    console.log("construct App...");
    super(props);
    this._onChange = this._onChange.bind(this);
    this._onMuteToggled = this._onMuteToggled.bind(this);

    this.state = {
      textValue: 'text',
      muted: false
    }
  }

  _onChange(event) {
    console.log("_onChange");
    console.log(event.value);
    let newStr = ""
    for (let i = 0; i < event.value.length; i++) {
      if (event.value.length > 1 && i === 0) continue;
      newStr = newStr + event.value[i];
    }
    this.setState({textValue:newStr});
  }
  _onMuteToggled(toggled) {
    this.setState({
      muted: toggled
    });
  }

  render() {
    // Uncomment here to watch the animated flex box example in action
    // return (
    //   <View {...styles.container}>
    //     <AnimatedFlexBoxExample />
    //   </View>
    // );

    const muteBackgroundColor = this.state.muted ? 'ff66FDCF' : 'ff17191f';
    const muteTextColor = this.state.muted ? 'ff17191f' : 'ff66FDCF';

    const sliderFillColor = 'ff66FDCF';
    const sliderTrackColor = 'ff626262';

    return (
      <View {...styles.container}>
        <View {...styles.content}>
          <Image source={require('./logo.png')} {...styles.logo} />
          <TextInput
            // value="text"
            value={this.state.textValue}
            placeholder="init"
            maxlength={20}
            // onInput={(e) => console.log(`App.js onInput: ${e.value}`)}
            // onChange={(e) => console.log(`App.js onChange: ${e.value}`)}
            onInput={this._onChange}
            // readonly
            {...styles.text_input}
          />
          <Text {...styles.sameple_text}>Sample Text</Text>
        </View>
      </View>
    );
  }
}

const styles = {
  container: {
    width: '100%',
    height: '100%',
    backgroundColor: 'ff17191f',
    justifyContent: 'center',
    alignItems: 'center',
  },
  content: {
    flex: 1.0,
    flexDirection: 'column',
    justifyContent: 'space-around',
    alignItems: 'center',
    padding: 24.0,
    maxWidth: 600,
    aspectRatio: 400.0 / 240.0,
  },
  logo: {
    flex: 0.0,
    width: '80%',
    aspectRatio: 281.6 / 35.0,
    placement: Image.PlacementFlags.centred,
  },
  knob: {
    minWidth: 100.0,
    minHeight: 100.0,
    width: '55%',
    height: '55%',
    marginTop: 15,
    marginBottom: 15,
    justifyContent: 'center',
    alignItems: 'center',
  },
  label: {
    flex: 1.0,
    justifyContent: 'center',
    alignItems: 'center',
    interceptClickEvents: false,
  },
  meter: {
    flex: 0.0,
    width: 100.0,
    height: 16.0,
  },
  canvas: {
    flex: 0.0,
    width: 100.0,
    height: 2,
    marginTop: 10,
  },
  mute_button: {
    justifyContent: 'center',
    alignItems: 'center',
    borderRadius: 5.0,
    borderWidth: 2.0,
    marginTop: 10,
    minWidth: 30.0,
    minHeight: 30.0,
    width: '20%',
    height: '17.5%',
  },
  mute_button_text: {
    fontSize: 20.0,
    lineSpacing: 1.6,
    fontStyle: Text.FontStyleFlags.bold,
  },
  sameple_text: {
    fontSize: 20.0,
    lineSpacing: 1.6,
    color: 'ffffffff',
    fontStyle: Text.FontStyleFlags.bold,
    'kerning-factor': 0.5,
  },
  text_input: {
    backgroundColor: 'ff17ffff',
    color: 'ff66FDCF',
    fontSize: 30.0,
    fontFamily: 'Menlo',
    fontStyle: Text.FontStyleFlags.bold,
    'kerning-factor': 0.5,
    'placeholder-color': 'ffaaaaaa',
    height: 50,
    width: 200,
  }
};

export default App;
