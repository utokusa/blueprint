import React, { Component, PropsWithChildren } from 'react';
import { SyntheticKeyboardEvent, SyntheticMouseEvent, SyntheticInputEvent } from '../lib/SyntheticEvents';
import { View } from './View';

export interface TextInputProps {
  placeholder?: string
  maxlength?: number
  onChange?: (keyCode: number, key: string) => void
  onInput?: (value: string) => void
}

type TextInputState = {
}

export class TextInput extends Component<PropsWithChildren<TextInputProps | any>, TextInputState> {
  constructor(props: PropsWithChildren<TextInputProps | any>) {
    super(props);
    console.log("construct TextInput (ts)");

    this._onKeyPressed = this._onKeyPressed.bind(this);
    this._onInput = this._onInput.bind(this);
    this._onMouseDown = this._onMouseDown.bind(this);

    this.state = {
    };
  }

  _onKeyPressed(e: SyntheticKeyboardEvent) {
    console.log("_onKeyPressed(e)");

    if (typeof this.props.onChange === 'function') {
      this.props.onChange(e.keyCode, e.key);
    }
  }

  _onMouseDown(e: SyntheticMouseEvent) {
    console.log("TextInput.tsx _onMouseDown");
  }

  _onInput(e: SyntheticInputEvent) {
    this.props.onInput(e.value);
  }

  render() {
    // return (
    //   // <View
    //   //   {...this.props}
    //   //   onMouseDown={this._onMouseDown}
    //   //   onKeyPress={this._onKeyPressed}
    //   // >
    //   //    {/*{React.createElement('TextInput', this.props, this.props.children)}*/}
    //   //   {this.props.children}
    //   // </View>
    //   React.createElement('TextInput', Object.assign({}, this.props, {
    //     onMouseDown: (e: SyntheticMouseEvent) => { this._onMouseDown(e) },
    //     onKeyPress: (e: SyntheticKeyboardEvent) => { this._onKeyPressed(e) }
    //   }), this.props.children)
    // );
    return React.createElement('TextInput', Object.assign({}, this.props, {
      onMouseDown: (e: SyntheticMouseEvent) => { this._onMouseDown(e) },
      onKeyPress: (e: SyntheticKeyboardEvent) => { this._onKeyPressed(e) },
      onInput: (e: SyntheticInputEvent) => { this._onInput(e) }
    }), this.props.children);
  }
};