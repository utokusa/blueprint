import React, { Component, PropsWithChildren } from 'react';
import { SyntheticMouseEvent } from '../lib/SyntheticEvents';

// export function TextInput(props: any) {
//     return React.createElement('TextInput', props, props.children);
// }

export interface TextInputProps {
  placeholder?: string
  maxlength?: number
  onChange?: (value: number) => void
}

type TextInputState = {
}

export class TextInput extends Component<PropsWithChildren<TextInputProps | any>, TextInputState> {
  render() {
    return (
      React.createElement('TextInput', this.props, this.props.children)
    );
  }
};